#pragma once

#include <ntddk.h>
#include <NTDDK.h>

#define DRIVER_NAME L"\\Driver\\Kbdclass"
#define DELAY_ONE_MILLISECOND -10

ULONG gC2pKeyCount;

NTSTATUS ObReferenceObjectByName(
	PUNICODE_STRING ObjectName,
	ULONG Attributes,
	PACCESS_STATE PassedAccessState,
	ACCESS_MASK DesiredAccess,
	POBJECT_TYPE ObjectType,
	KPROCESSOR_MODE AccessMode,
	PVOID ParseContext,
	PVOID *Object);
extern POBJECT_TYPE IoDriverObjectType;

typedef struct _C2P_DEV_EXT
{
	ULONG NodeSize;
	PDEVICE_OBJECT pFilterDeviceObject;
	KSPIN_LOCK IoRequestspinLock;
	KEVENT IoInProgressEvent;
	PDEVICE_OBJECT TargetDeviceObject;
	PDEVICE_OBJECT LowerDeviceObject;
}C2P_DEV_EXT, *PC2P_DEV_EXT;

typedef struct _KEYBOARD_INPUT_DATA {
	USHORT UnitId;
	USHORT MakeCode;
	USHORT Flags;
	USHORT Reserved;
	ULONG ExtraInformation;
}KEYBOARD_INPUT_DATA, *PKEYBOARD_INPUT_DATA;