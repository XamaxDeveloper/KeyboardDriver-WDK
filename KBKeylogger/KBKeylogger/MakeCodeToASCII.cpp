#include "Header.h"

VOID MakeCodeToASCII(USHORT MakeCode, USHORT Flags, PCHAR Ascii)//Ascii
{
	if (Flags >= 2)
	{
		if (Flags == 2)
		{
			switch (MakeCode)
			{
			case 0x2a:
			{
				strncpy(Ascii, " ", 16);
				break;
			}
			case 0x5b:
			case 0x5c:
			{
				strncpy(Ascii, "WindowsDOWN", 16);
				break;
			}
			case 0x48:
			{
				strncpy(Ascii, "UpDOWN", 16);
				break;
			}
			case 0x50:
			{
				strncpy(Ascii, "DownDOWN", 16);
				break;
			}
			case 0x4b:
			{
				strncpy(Ascii, "LeftDOWN", 16);
				break;
			}
			case 0x4d:
			{
				strncpy(Ascii, "RightDOWN", 16);
				break;
			}
			case 0x53:
			{
				strncpy(Ascii, "DelDOWN", 16);
				break;
			}
			default:
			{
				strncpy(Ascii, "Error", 16);
				break;
			}
			}
		}
		if (Flags == 3)
		{
			switch (MakeCode)
			{
			case 0x2a:
			{
				strncpy(Ascii, " ", 16);
				break;
			}
			case 0x5b:
			case 0x5c:
			{
				strncpy(Ascii, "WindowsUP", 16);
				break;
			}
			case 0x48:
			{
				strncpy(Ascii, "UpUP", 16);
				break;
			}
			case 0x50:
			{
				strncpy(Ascii, "DownUP", 16);
				break;
			}
			case 0x4b:
			{
				strncpy(Ascii, "LeftUP", 16);
				break;
			}
			case 0x4d:
			{
				strncpy(Ascii, "RightUP", 16);
				break;
			}
			case 0x53:
			{
				strncpy(Ascii, "DelUP", 16);
				break;
			}
			default:
			{
				strncpy(Ascii, "Error", 16);
				break;
			}
			}
		}
		return;
	}
	switch (MakeCode)
	{
	case 0x1d:
	{
		strncpy(Ascii, "Ctrl", 12);
		break;
	}
	case 0x1c:
	{
		strncpy(Ascii, "Enter", 12);
		break;
	}
	case 0x3a:
	{
		strncpy(Ascii, "CapsLock", 12);
		break;
	}
	case 0x2a:
	case 0x36:
	{
		strncpy(Ascii, "Shift", 12);
		break;
	}
	case 0x02:
	{
		strncpy(Ascii, "1", 12);
		break;
	}
	case 0x4f:
	{
		strncpy(Ascii, "Num1", 12);
		break;
	}
	case 0x03:
	{
		strncpy(Ascii, "2", 12);
		break;
	}
	case 0x50:
	{
		strncpy(Ascii, "Num2", 12);
		break;
	}
	case 0x04:
	{
		strncpy(Ascii, "3", 12);
		break;
	}
	case 0x51:
	{
		strncpy(Ascii, "Num3", 12);
		break;
	}
	case 0x05:
	{
		strncpy(Ascii, "4", 12);
		break;
	}
	case 0x4b:
	{
		strncpy(Ascii, "Num4", 12);
		break;
	}
	case 0x06:
	{
		strncpy(Ascii, "5", 12);
		break;
	}
	case 0x4c:
	{
		strncpy(Ascii, "Num5", 12);
		break;
	}
	case 0x07:
	{
		strncpy(Ascii, "6", 12);
		break;
	}
	case 0x4d:
	{
		strncpy(Ascii, "Num6", 12);
		break;
	}
	case 0x08:
	{
		strncpy(Ascii, "7", 12);
		break;
	}
	case 0x47:
	{
		strncpy(Ascii, "Num7", 12);
		break;
	}
	case 0x09:
	{
		strncpy(Ascii, "8", 12);
		break;
	}
	case 0x48:
	{
		strncpy(Ascii, "Num8", 12);
		break;
	}
	case 0x0a:
	{
		strncpy(Ascii, "9", 12);
		break;
	}
	case 0x49:
	{
		strncpy(Ascii, "Num9", 12);
		break;
	}
	case 0x0b:
	{
		strncpy(Ascii, "0", 12);
		break;
	}
	case 0x52:
	{
		strncpy(Ascii, "Num0", 12);
		break;
	}
	case 0x1e:
	{
		strncpy(Ascii, "a", 12);
		break;
	}
	case 0x30:
	{
		strncpy(Ascii, "b", 12);
		break;
	}
	case 0x2e:
	{
		strncpy(Ascii, "c", 12);
		break;
	}
	case 0x20:
	{
		strncpy(Ascii, "d", 12);
		break;
	}
	case 0x12:
	{
		strncpy(Ascii, "e", 12);
		break;
	}
	case 0x21:
	{
		strncpy(Ascii, "f", 12);
		break;
	}
	case 0x22:
	{
		strncpy(Ascii, "g", 12);
		break;
	}
	case 0x23:
	{
		strncpy(Ascii, "h", 12);
		break;
	}
	case 0x17:
	{
		strncpy(Ascii, "i", 12);
		break;
	}
	case 0x24:
	{
		strncpy(Ascii, "j", 12);
		break;
	}
	case 0x25:
	{
		strncpy(Ascii, "k", 12);
		break;
	}
	case 0x26:
	{
		strncpy(Ascii, "l", 12);
		break;
	}
	case 0x32:
	{
		strncpy(Ascii, "m", 12);
		break;
	}
	case 0x31:
	{
		strncpy(Ascii, "n", 12);
		break;
	}
	case 0x18:
	{
		strncpy(Ascii, "o", 12);
		break;
	}
	case 0x19:
	{
		strncpy(Ascii, "p", 12);
		break;
	}
	case 0x10:
	{
		strncpy(Ascii, "q", 12);
		break;
	}
	case 0x13:
	{
		strncpy(Ascii, "r", 12);
		break;
	}
	case 0x1f:
	{
		strncpy(Ascii, "s", 12);
		break;
	}
	case 0x14:
	{
		strncpy(Ascii, "t", 12);
		break;
	}
	case 0x16:
	{
		strncpy(Ascii, "u", 12);
		break;
	}
	case 0x2f:
	{
		strncpy(Ascii, "v", 12);
		break;
	}
	case 0x11:
	{
		strncpy(Ascii, "w", 12);
		break;
	}
	case 0x2d:
	{
		strncpy(Ascii, "x", 12);
		break;
	}
	case 0x15:
	{
		strncpy(Ascii, "y", 12);
		break;
	}
	case 0x2c:
	{
		strncpy(Ascii, "z", 12);
		break;
	}
	case 0x39:
	{
		strncpy(Ascii, "Space", 12);
		break;
	}
	case 0x0e:
	{
		strncpy(Ascii, "BackSpace", 12);
		break;
	}
	case 0x0f:
	{
		strncpy(Ascii, "Tab", 12);
		break;
	}
	case 0x45:
	{
		strncpy(Ascii, "NumLock", 12);
		break;
	}
	case 0x33:
	{
		strncpy(Ascii, ",", 12);
		break;
	}
	case 0x34:
	{
		strncpy(Ascii, ".", 12);
		break;
	}
	case 0x35:
	{
		strncpy(Ascii, "/", 12);
		break;
	}
	case 0x27:
	{
		strncpy(Ascii, ";", 12);
		break;
	}
	case 0x28:
	{
		strncpy(Ascii, "'", 12);
		break;
	}
	case 0x1a:
	{
		strncpy(Ascii, "[", 12);
		break;
	}
	case 0x1b:
	{
		strncpy(Ascii, "]", 12);
		break;
	}
	case 0x2b:
	{
		strncpy(Ascii, "\\", 12);
		break;
	}
	case 0x0c:
	{
		strncpy(Ascii, "-", 12);
		break;
	}
	case 0x0d:
	{
		strncpy(Ascii, "=", 12);
		break;
	}
	default:
	{
		strncpy(Ascii, "Error", 12);
		return;
	}
	}
	if (Flags == 0)
	{
		strncat(Ascii, "DOWN", 4);
	}
	else
	{
		strncat(Ascii, "UP", 4);
	}
	return;
}