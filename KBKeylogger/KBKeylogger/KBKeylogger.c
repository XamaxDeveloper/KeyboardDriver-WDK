#include "Header.h"
#include "DispatchFunction.c"





NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING RegistryPath)
{
	ULONG temp;
	UNICODE_STRING kbkname;
	NTSTATUS status;
	PDRIVER_OBJECT kbkdriver = NULL;
	PC2P_DEV_EXT devExt;

	PDEVICE_OBJECT pFilterDriver = NULL;//Привод фильтра
	PDEVICE_OBJECT pTargetDriver = NULL;//Целевой драйвер
	PDEVICE_OBJECT pLowerDriver = NULL;//Привод снизу

	DbgPrint("DriverStatus:DriverON");

	gC2pKeyCount = 0;

		for (temp = 0; temp < IRP_MJ_MAXIMUM_FUNCTION; ++temp)
		{
		driver->MajorFunction[temp] = DispatchGeneral;
		}
		driver->MajorFunction[IRP_MJ_READ] = Read;
		driver->MajorFunction[IRP_MJ_POWER] = Power;
		driver->MajorFunction[IRP_MJ_PNP] = PNP;
		driver->DriverUnload = DriverUnload;

		RtlInitUnicodeString(&kbkname, DRIVER_NAME);

		status = ObReferenceObjectByName(&kbkname, OBJ_CASE_INSENSITIVE, NULL, FILE_ALL_ACCESS,
											IoDriverObjectType, KernelMode, NULL, &kbkdriver);

		if (!NT_SUCCESS(status))
		{
			DbgPrint("DriverStatus:ObReferenceObjectByName_RETURN_ERROR");
			return status;
		}
		else
		{
			ObDereferenceObject(driver);
		}

		pTargetDriver = kbkdriver->DeviceObject;

		while (pTargetDriver)
		{
			status = IoCreateDevice(driver, sizeof(C2P_DEV_EXT), NULL, pTargetDriver->DeviceType,
				pTargetDriver->Characteristics, FALSE, &pFilterDriver);
			if (!NT_SUCCESS(status))
			{
				DbgPrint("DriverStatus:FAILED_TO_CREATE_FILTER_DEVICE");
				return status;
			}
			pLowerDriver = IoAttachDeviceToDeviceStack(pFilterDriver, pTargetDriver);
			if (!pLowerDriver)
			{
				DbgPrint("DEVICE_BINDING_FAILED");
				IoDeleteDevice(pFilterDriver);
				pFilterDriver = NULL;
				return status;
			}

			devExt = (PC2P_DEV_EXT)(pFilterDriver->DeviceExtension);
			memset(devExt, 0, sizeof(C2P_DEV_EXT));
			devExt->NodeSize = sizeof(C2P_DEV_EXT);
			KeInitializeSpinLock(&(devExt->IoRequestspinLock));
			KeInitializeEvent(&(devExt->IoInProgressEvent), NotificationEvent, FALSE);
			devExt->TargetDeviceObject = pTargetDriver;
			devExt->LowerDeviceObject = pLowerDriver;
			pFilterDriver->DeviceType = pLowerDriver->DeviceType;
			pFilterDriver->Characteristics = pLowerDriver->Characteristics;
			pFilterDriver->StackSize = pLowerDriver->StackSize + 1;
			pFilterDriver->Flags |= pLowerDriver->Flags&(DO_BUFFERED_IO | DO_POWER_PAGABLE);
			pTargetDriver = pTargetDriver->NextDevice;
			
		}
		return STATUS_SUCCESS;
}
