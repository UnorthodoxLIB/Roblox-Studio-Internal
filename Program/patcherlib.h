#pragma once

#define CURL_STATICLIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <curl/curl.h>

#pragma comment(lib, "Ws2_32.lib")

// Updates patcher signatures (Just signatures)
void updatePatcherSignatures();
// Updates patcher Patchs (Just patches)
void updatePatcherPatches();
// Updates patcher data (Signatures & Patches)
void updatePatcherData();
// Patches studio, studio path being the path to RobloxStudioBeta.exe, createInternalAt being where you want the file to be created, & what you want its name to be.
char PatchStudio(const char* studioPath,const char* createInternalAt);