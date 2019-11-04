//
//
//

#ifndef AEYON3D_KEY_HPP
#define AEYON3D_KEY_HPP

#include <cstdint>

namespace aeyon
{
	enum class KeyCode : std::uint32_t
	{
		Unknown = 0,

		A = 4,
		B = 5,
		C = 6,
		D = 7,
		E = 8,
		F = 9,
		G = 10,
		H = 11,
		I = 12,
		J = 13,
		K = 14,
		L = 15,
		M = 16,
		N = 17,
		O = 18,
		P = 19,
		Q = 20,
		R = 21,
		S = 22,
		T = 23,
		U = 24,
		V = 25,
		W = 26,
		X = 27,
		Y = 28,
		Z = 29,

		Alpha1 = 30,
		Alpha2 = 31,
		Alpha3 = 32,
		Alpha4 = 33,
		Alpha5 = 34,
		Alpha6 = 35,
		Alpha7 = 36,
		Alpha8 = 37,
		Alpha9 = 38,
		Alpha0 = 39,

		Return = 40,
		Escape = 41,
		Backspace = 42,
		Tab = 43,
		Space = 44,

		Minus = 45,
		Equals = 46,
		LeftBracket = 47,
		RightBracket = 48,
		Backslash = 49,

		NonUSHash = 50, // Identical to 49, but almost never used
		Semicolon = 51,
		Apostrophe = 52,
		Grave = 53,
		Comma = 54,
		Period = 55,
		Slash = 56,

		CapsLock = 57,

		F1 = 58,
		F2 = 59,
		F3 = 60,
		F4 = 61,
		F5 = 62,
		F6 = 63,
		F7 = 64,
		F8 = 65,
		F9 = 66,
		F10 = 67,
		F11 = 68,
		F12 = 69,

		PrintScreen = 70,
		ScrollLock = 71,
		Pause = 72,
		Insert = 73,

		Home = 74,
		PageUp = 75,
		Delete = 76,
		End = 77,
		PageDown = 78,
		Right = 79,
		Left = 80,
		Down = 81,
		Up = 82,

		NumLockClear = 83,

		KeypadDivide = 84,
		KeypadMultiply = 85,
		KeypadMinus = 86,
		KeypadPlus = 87,
		KeypadEnter = 88,
		Keypad1 = 89,
		Keypad2 = 90,
		Keypad3 = 91,
		Keypad4 = 92,
		Keypad5 = 93,
		Keypad6 = 94,
		Keypad7 = 95,
		Keypad8 = 96,
		Keypad9 = 97,
		Keypad0 = 98,
		KeypadPeriod = 99,

		NonUSBackslash = 100, // Located between Left-Shift and Y on ISO keyboards

		Application = 101, // Windows contex menu, compose
		Power = 102, // Only a physical key on some MACs
		KeypadEquals = 103,
		F13 = 104,
		F14 = 105,
		F15 = 106,
		F16 = 107,
		F17 = 108,
		F18 = 109,
		F19 = 110,
		F20 = 111,
		F21 = 112,
		F22 = 113,
		F23 = 114,
		F24 = 115,
		Execute = 116,
		Help = 117,
		Menu = 118,
		Select = 119,
		Stop = 120,
		Again = 121,
		Undo = 122,
		Cut = 123,
		Copy = 124,
		Paste = 125,
		Find = 126,
		Mute = 127,
		VolumeUp = 128,
		VolumeDown = 129,

		KeypadComma = 133,
		KeypadEqualsAS400 = 134,

		International1 = 135,
		International2 = 136,
		International3 = 137, // Yen
		International4 = 138,
		International5 = 139,
		International6 = 140,
		International7 = 141,
		International8 = 142,
		International9 = 143,
		Lang1 = 144, // Hangul/English toggle
		Lang2 = 145, // Hanja conversion
		Lang3 = 146, // Katakana
		Lang4 = 147, // Hiragana
		Lang5 = 148, // Zenkaku/Hankaku
		Lang6 = 149, // reserved
		Lang7 = 150, // reserved
		Lang8 = 151, // reserved
		Lang9 = 152, // reserved

		AltErase = 153, // Erase-Eaze
		SysReq = 154,
		Cancel = 155,
		Clear = 156,
		Prior = 157,
		Return2 = 158,
		Separator = 159,
		Out = 160,
		Oper = 161,
		ClearAgain = 162,
		CRSel = 163,
		EXSel = 164,

		Keypad00 = 176,
		Keypad000 = 177,
		ThousandsSeparator = 178,
		DecimalSeparator = 179,
		CurrencyUnit = 180,
		CurrencySubUnit = 181,
		KeypadLeftParen = 182,
		KeypadRightParen = 183,
		KeypadLeftBrace = 184,
		KeypadRightBrace = 185,
		KeypadTab = 186,
		KeypadBackspace = 187,
		KeypadA = 188,
		KeypadB = 189,
		KeypadC = 190,
		KeypadD = 191,
		KeypadE = 192,
		KeypadF = 193,
		KeypadXOR = 194,
		KeypadPower = 195,
		KeypadPercent = 196,
		KeypadLess = 197,
		KeypadGreater = 198,
		KeypadAmpersand = 199,
		KeypadDoubleAmpersand = 200,
		KeypadVerticalBar = 201,
		KeypadDoubleVerticalBar = 202,
		KeypadColon = 203,
		KeypadHash = 204,
		KeypadSpace = 205,
		KeypadAt = 206,
		KeypadExclaim = 207,
		KeypadMemStore = 208,
		KeypadMemRecall = 209,
		KeypadMemClear = 210,
		KeypadMemAdd = 211,
		KeypadMemSubtract = 212,
		KeypadMemMultiply = 213,
		KeypadMemDivide = 214,
		KeypadPlusMinus = 215,
		KeypadClear = 216,
		KeypadClearEntry = 217,
		KeypadBinary = 218,
		KeypadOctal = 219,
		KeypadDecimal = 220,
		KeypadHexadecimal = 221,

		LeftControl = 224,
		LeftShift = 225,
		LeftAlt = 226,
		LeftGUI = 227, // Windows, Command, Meta
		RightControl = 228,
		RightShift = 229,
		RightAlt = 230, // Alt Gr, Option
		RightGUI = 231 // Windows, Command, Meta
	};
}

#endif //AEYON3D_KEY_HPP
