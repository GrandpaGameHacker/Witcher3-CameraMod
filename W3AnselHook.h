#include <windows.h>
#include <cstdint>
#pragma once
static const char szNvCamera[] = "NvCamera64.dll";
static const char szGame[] = "witcher3.exe";

#define ANSEL_OFFSET1 0x2A42C //
static const BYTE ANSEL_PATCH1[] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90};

#define ANSEL_OFFSET2 0x2AB1B //
static const BYTE ANSEL_PATCH2[] = {0xB0, 0x01, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90};

#define W3OFFSET1 0x11AD8A // 74 12 48 8B 5C 24 50
static const BYTE W3PATCH1[] = {0xEB};


void __declspec(dllexport) patch();
void __declspec(dllexport) patch_address(uintptr_t address, const BYTE* bytes, size_t length);