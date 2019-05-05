#include "Header.h"

VOID DriverUnload(PDRIVER_OBJECT driver)
{
	PC2P_DEV_EXT devExt;
	PDEVICE_OBJECT DeviceObject;
	LARGE_INTEGER lDelay;
	PRKTHREAD CurrentThread;
	lDelay = RtlConvertLongToLargeInteger(100 * DELAY_ONE_MILLISECOND);
	CurrentThread = KeGetCurrentThread();
	KeSetPriorityThread(CurrentThread, LOW_REALTIME_PRIORITY);
	UNREFERENCED_PARAMETER(driver);
	DeviceObject = driver->DeviceObject;
	while (DeviceObject)
	{
		devExt = (PC2P_DEV_EXT)(DeviceObject->DeviceExtension);
		IoDetachDevice(devExt->LowerDeviceObject);
		IoDeleteDevice(DeviceObject);
		DeviceObject = DeviceObject->NextDevice;
	}
	ASSERT(NULL == driver->DeviceObject);
	while (gC2pKeyCount)
	{
		KeDelayExecutionThread(KernelMode, FALSE, &lDelay);
	}
	DbgPrint("DriverStatus:DriverOFF");
	return;
}

NTSTATUS DispatchGeneral(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	DbgPrint("DriverStatus:AdditionInfo");
	IoSkipCurrentIrpStackLocation(Irp);
	return IoCallDriver(((PC2P_DEV_EXT)DeviceObject->DeviceExtension)->LowerDeviceObject, Irp);
}

NTSTATUS PNP(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS status = STATUS_SUCCESS;
	PC2P_DEV_EXT devExt;
	PIO_STACK_LOCATION irpstack;
	devExt = (PC2P_DEV_EXT)(DeviceObject->DeviceExtension);
	irpstack = IoGetCurrentIrpStackLocation(Irp);
	switch (irpstack->MinorFunction)
	{
	case IRP_MN_REMOVE_DEVICE:
	{
		DbgPrint("DriverStatus:there is a USB keyboard output (PNP request)");
		IoSkipCurrentIrpStackLocation(Irp);
		IoCallDriver(devExt->LowerDeviceObject, Irp);
		IoDetachDevice(devExt->LowerDeviceObject);
		IoDeleteDevice(DeviceObject);
		status = STATUS_SUCCESS;
		break;
	}
	default:
	{
		IoSkipCurrentIrpStackLocation(Irp);
		status = IoCallDriver(devExt->LowerDeviceObject, Irp);
		break;
	}
	}
	return status;
}

NTSTATUS Power(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	PC2P_DEV_EXT devExt;
	PoStartNextPowerIrp(Irp);
	IoSkipCurrentIrpStackLocation(Irp);
	devExt = (PC2P_DEV_EXT)DeviceObject->DeviceExtension;
	return PoCallDriver(devExt->LowerDeviceObject, Irp);
}

NTSTATUS ReadComplete(PDEVICE_OBJECT DeviceObject, PIRP Irp, PVOID Context)
{
	PIO_STACK_LOCATION stackirp;
	ULONG buf_len = 0;
	ULONG i;
	PKEYBOARD_INPUT_DATA KeyData;
	PCHAR Ascii = "1234567890123456";
	stackirp = IoGetCurrentIrpStackLocation(Irp);
	if (NT_SUCCESS(Irp->IoStatus.Status))
	{
		buf_len = Irp->IoStatus.Information / sizeof(KEYBOARD_INPUT_DATA);
		KeyData = Irp->AssociatedIrp.SystemBuffer;
		for (i = 0; i < buf_len; i++)
		{
			MakeCodeToASCII(KeyData->MakeCode, KeyData->Flags, Ascii);
			DbgPrint("DriverStatus:%s", Ascii);
		}
	}
	gC2pKeyCount--;
	if (Irp->PendingReturned)
	{
		IoMarkIrpPending(Irp);
	}
	return Irp->IoStatus.Status;
}



NTSTATUS Read(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS status = STATUS_SUCCESS;
	PC2P_DEV_EXT devExt;
	PIO_STACK_LOCATION currentirpstack;
	KEVENT waitEvent;
	KeInitializeEvent(&waitEvent, NotificationEvent, FALSE);
	if (Irp->CurrentLocation == 1)
	{
		DbgPrint("DriverStatus:Drives capture had faced about current location");
		status = STATUS_INVALID_DEVICE_REQUEST;
		Irp->IoStatus.Status = status;
		Irp->IoStatus.Information = 0;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		return status;
	}
	gC2pKeyCount++;
	devExt = (PC2P_DEV_EXT)(DeviceObject->DeviceExtension);
	currentirpstack = IoGetCurrentIrpStackLocation(Irp);
	IoCopyCurrentIrpStackLocationToNext(Irp);
	IoSetCompletionRoutine(Irp, ReadComplete, DeviceObject, TRUE, TRUE, TRUE);
	return IoCallDriver(devExt->LowerDeviceObject, Irp);
}
