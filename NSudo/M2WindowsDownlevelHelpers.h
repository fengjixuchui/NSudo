﻿/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2WindowsDownlevelHelpers.h
 * PURPOSE:   Definition for the Windows downlevel helper functions
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#pragma once

#ifndef _M2_WINDOWS_DOWNLEVEL_HELPERS_
#define _M2_WINDOWS_DOWNLEVEL_HELPERS_

#include <Windows.h>

/**
 * Retrieves the calling thread's last-error code value. The last-error code is
 * maintained on a per-thread basis. Multiple threads do not overwrite each
 * other's last-error code.
 *
 * @param IsLastFunctionCallSucceeded Set this parameter TRUE if you can be
 *                                    sure that the last call was succeeded.
 *                                    Otherwise, set this parameter FALSE.
 * @param UseLastErrorWhenSucceeded Set this parameter TRUE if you want to use
 *                                  last-error code if the last call was
 *                                  succeeded. Otherwise, set this parameter
 *                                  FALSE.
 * @return The calling thread's last-error code.
 */
DWORD M2GetLastWin32Error(
    _In_ BOOL IsLastFunctionCallSucceeded = FALSE,
    _In_ BOOL UseLastErrorWhenSucceeded = FALSE);

/**
 * Retrieves the calling thread's last-error code value. The last-error code is
 * maintained on a per-thread basis. Multiple threads do not overwrite each
 * other's last-error code.
 *
 * @param KnownFailed Set this parameter TRUE if you can be sure that the last
 *                    call was failed, Otherwise, set this parameter FALSE.
 * @param LastErrorCode A pointer to a variable that returns the calling
 *                      thread's last-error code. This parameter can be NULL.
 * @return The calling thread's last-error code which is converted to an
 *         HRESULT value.
 */
HRESULT M2GetLastHResultError(
    _In_ BOOL IsLastFunctionCallSucceeded = FALSE,
    _In_ BOOL UseLastErrorWhenSucceeded = FALSE);

/**
 * Allocates a block of memory from a heap. The allocated memory is not
 * movable.
 *
 * @param lpNewMem A pointer to the allocated memory block.
 * @param hHeap A handle to the heap from which the memory will be allocated.
 * @param dwFlags The heap allocation options.
 * @param dwBytes The number of bytes to be allocated.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see HeapAlloc.
 */
HRESULT M2HeapAlloc(
    _Out_ PVOID* lpNewMem,
    _In_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ SIZE_T dwBytes);

/**
 * Reallocates a block of memory from a heap. This function enables you to
 * resize a memory block and change other memory block properties. The
 * allocated memory is not movable.
 *
 * @param lpNewMem A pointer to the allocated memory block.
 * @param hHeap A handle to the heap from which the memory is to be
 *              reallocated.
 * @param dwFlags The heap reallocation options.
 * @param lpMem A pointer to the block of memory that the function reallocates.
 * @param dwBytes The new size of the memory block, in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK. If the
 *         function fails, the original memory is not freed, and the original
 *         handle and pointer are still valid.
 * @remark For more information, see HeapReAlloc.
 */
HRESULT M2HeapReAlloc(
    _Out_ PVOID* lpNewMem,
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ LPVOID lpMem,
    _In_ SIZE_T dwBytes);

/**
 * Frees a memory block allocated from a heap by the M2HeapAlloc and
 * M2HeapReAlloc function.
 *
 * @param hHeap A handle to the heap whose memory block is to be freed.
 * @param dwFlags The heap free options.
 * @param lpMem A pointer to the memory block to be freed.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see HeapFree.
 */
HRESULT M2HeapFree(
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ LPVOID lpMem);

/**
 * Closes an open object handle.
 *
 * @param hObject A valid handle to an open object.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CloseHandle.
 */
HRESULT M2CloseHandle(
    _In_ HANDLE hObject);

/**
 * Creates a thread to execute within the virtual address space of the calling
 * process.
 *
 * @param lpThreadHandle The address of the returned handle to the new thread.
 * @param lpThreadAttributes A pointer to a SECURITY_ATTRIBUTES structure that
 *                           determines whether the returned handle can be
 *                           inherited by child processes.
 * @param dwStackSize The initial size of the stack, in bytes.
 * @param lpStartAddress A pointer to the application-defined function to be
 *                       executed by the thread.
 * @param lpParameter A pointer to a variable to be passed to the thread.
 * @param dwCreationFlags The flags that control the creation of the thread.
 * @param lpThreadId A pointer to a variable that receives the thread
 *                   identifier.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CreateThread.
 */
HRESULT M2CreateThread(
    _Out_ PHANDLE lpThreadHandle,
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ SIZE_T dwStackSize,
    _In_ LPTHREAD_START_ROUTINE lpStartAddress,
    _In_opt_ LPVOID lpParameter,
    _In_ DWORD dwCreationFlags,
    _Out_opt_ LPDWORD lpThreadId);

/**
 * Retrieves the number of logical processors in the current group.
 *
 * @return The number of logical processors in the current group.
 */
DWORD M2GetNumberOfHardwareThreads();

/**
 * Retrieves the number of milliseconds that have elapsed since the system was
 * started.
 *
 * @return The number of milliseconds.
 */
ULONGLONG M2GetTickCount();

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Creates or opens a file or I/O device. The most commonly used I/O devices
 * are as follows: file, file stream, directory, physical disk, volume, console
 * buffer, tape drive, communications resource, mailslot, and pipe. The
 * function returns a handle that can be used to access the file or device for
 * various types of I/O depending on the file or device and the flags and
 * attributes specified.
 *
 * @param lpFileHandle The address of the returned handle to the specified
 *                     file.
 * @param lpFileName The name of the file or device to be created or opened.
 *                   You may use either forward slashes (/) or backslashes ()
 *                   in this name.
 * @param dwDesiredAccess The requested access to the file or device, which can
 *                        be summarized as read, write, both or neither zero).
 * @param dwShareMode The requested sharing mode of the file or device, which
 *                    can be read, write, both, delete, all of these, or none
 *                    (refer to the following table). Access requests to
 *                    attributes or extended attributes are not affected by
 *                    this flag.
 * @param lpSecurityAttributes A pointer to a SECURITY_ATTRIBUTES structure
 *                             that contains two separate but related data
 *                             members: an optional security descriptor, and a
 *                             Boolean value that determines whether the
 *                             returned handle can be inherited by child
 *                             processes. This parameter can be NULL.
 * @param dwCreationDisposition An action to take on a file or device that
 *                              exists or does not exist.
 * @param dwFlagsAndAttributes The file or device attributes and flags,
 *                             FILE_ATTRIBUTE_NORMAL being the most common
 *                             default value for files.
 * @param hTemplateFile A valid handle to a template file with the GENERIC_READ
 *                      access right. The template file supplies file
 *                      attributes and extended attributes for the file that is
 *                      being created. This parameter can be NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CreateFileW.
 */
HRESULT M2CreateFile(
    _Out_ PHANDLE lpFileHandle,
    _In_ LPCWSTR lpFileName,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwShareMode,
    _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _In_ DWORD dwCreationDisposition,
    _In_ DWORD dwFlagsAndAttributes,
    _In_opt_ HANDLE hTemplateFile);

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Closes a handle to the specified registry key.
 *
 * @param hKey A handle to the open key to be closed.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see RegCloseKey.
 */
HRESULT M2RegCloseKey(
    _In_ HKEY hKey);

/**
 * Creates the specified registry key. If the key already exists, the function
 * opens it. Note that key names are not case sensitive.
 *
 * @param hKey A handle to an open registry key.
 * @param lpSubKey The name of a subkey that this function opens or creates
 * @param Reserved This parameter is reserved and must be zero.
 * @param lpClass The user-defined class type of this key.
 * @param dwOptions This parameter can be one of the following values:
 *                  REG_OPTION_BACKUP_RESTORE, REG_OPTION_CREATE_LINK,
 *                  REG_OPTION_NON_VOLATILE, REG_OPTION_VOLATILE.
 * @param samDesired A mask that specifies the access rights for the key to be
 *                   created.
 * @param lpSecurityAttributes A pointer to a SECURITY_ATTRIBUTES structure
 *                             that determines whether the returned handle can
 *                             be inherited by child processes.
 * @param phkResult A pointer to a variable that receives a handle to the
 *                  opened or created key.
 * @param lpdwDisposition A pointer to a variable that receives one of the
 *                        following disposition values.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see RegCreateKeyEx.
 */
HRESULT M2RegCreateKey(
    _In_ HKEY hKey,
    _In_ LPCWSTR lpSubKey,
    _Reserved_ DWORD Reserved,
    _In_opt_ LPWSTR lpClass,
    _In_ DWORD dwOptions,
    _In_ REGSAM samDesired,
    _In_opt_ CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _Out_ PHKEY phkResult,
    _Out_opt_ LPDWORD lpdwDisposition);

/**
 * Retrieves the type and data for the specified value name associated with an
 * open registry key.
 *
 * @param hKey A handle to an open registry key.
 * @param lpValueName The name of the registry value.
 * @param lpReserved This parameter is reserved and must be NULL.
 * @param lpType A pointer to a variable that receives a code indicating the
 *              type of data stored in the specified value.
 * @param lpData A pointer to a buffer that receives the value's data.
 * @param lpcbData A pointer to a variable that specifies the size of the
 *                 buffer pointed to by the lpData parameter, in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see RegQueryValueEx.
 */
HRESULT M2RegQueryValue(
    _In_ HKEY hKey,
    _In_opt_ LPCWSTR lpValueName,
    _Reserved_ LPDWORD lpReserved,
    _Out_opt_ LPDWORD lpType,
    _Out_opt_ LPBYTE lpData,
    _Inout_opt_ LPDWORD lpcbData);

/**
 * Retrieves the type and data for the specified value name associated with an
 * open registry key.
 *
 * @param hKey A handle to an open registry key.
 * @param lpValueName The name of the value to be set.
 * @param Reserved This parameter is reserved and must be zero.
 * @param dwType The type of data pointed to by the lpData parameter.
 * @param lpData The data to be stored.
 * @param cbData The size of the information pointed to by the lpData
 *               parameter, in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see RegSetValueEx.
 */
HRESULT M2RegSetValue(
    _In_ HKEY hKey,
    _In_opt_ LPCWSTR lpValueName,
    _Reserved_ DWORD Reserved,
    _In_ DWORD dwType,
    _In_opt_ CONST BYTE* lpData,
    _In_ DWORD cbData);

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Loads the specified module with the optimization of the mitigation of DLL
 * preloading attacks into the address space of the calling process safely. The
 * specified module may cause other modules to be loaded.
 *
 * @param phLibModule A handle to the loaded module.
 * @param lpLibFileName A string that specifies the file name of the module to
 *                      load.
 * @param hFile This parameter is reserved for future use. It must be NULL.
 * @param dwFlags The action to be taken when loading the module.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see LoadLibraryEx.
 */
HRESULT M2LoadLibrary(
    _Out_ HMODULE* phLibModule,
    _In_ LPCWSTR lpLibFileName,
    _Reserved_ HANDLE hFile,
    _In_ DWORD dwFlags);

#endif

/**
 * Frees the loaded dynamic-link library (DLL) module and, if necessary,
 * decrements its reference count. When the reference count reaches zero, the
 * module is unloaded from the address space of the calling process and the
 * handle is no longer valid.
 *
 * @param hLibModule A handle to the loaded library module.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see FreeLibrary.
 */
HRESULT M2FreeLibrary(
    _In_ HMODULE hLibModule);

/**
 * Retrieves the address of an exported function or variable from the specified
 * dynamic-link library (DLL).
 *
 * @param lpProcAddress The address of the exported function or variable.
 * @param hModule A handle to the DLL module that contains the function or
 *                variable. The LoadLibrary, LoadLibraryEx, LoadPackagedLibrary
 *                or GetModuleHandle function returns this handle. This
 *                function does not retrieve addresses from modules that were
 *                loaded using the LOAD_LIBRARY_AS_DATAFILE flag. For more
 *                information, see LoadLibraryEx.
 * @param lpProcName The function or variable name, or the function's ordinal
 *                   value. If this parameter is an ordinal value, it must be
 *                   in the low-order word; the high-order word must be zero.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetProcAddress(
    _Out_ FARPROC* lpProcAddress,
    _In_ HMODULE hModule,
    _In_ LPCSTR lpProcName);

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Sends a control code directly to a specified device driver, causing the
 * corresponding device to perform the corresponding operation.
 *
 * @param hDevice A handle to the device on which the operation is to be
 *                performed.
 * @param dwIoControlCode The control code for the operation.
 * @param lpInBuffer A pointer to the input buffer that contains the data
 *                   required to perform the operation. This parameter can be
 *                   NULL if dwIoControlCode specifies an operation that does
 *                   not require input data.
 * @param nInBufferSize The size of the input buffer, in bytes.
 * @param lpOutBuffer A pointer to the output buffer that is to receive the
 *                    data returned by the operation. This parameter can be
 *                    NULL if dwIoControlCode specifies an operation that does
 *                    not return data.
 * @param nOutBufferSize The size of the output buffer, in bytes.
 * @param lpBytesReturned A pointer to a variable that receives the size of
 *                        the data stored in the output buffer, in bytes.
 * @param lpOverlapped A pointer to an OVERLAPPED structure.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see DeviceIoControl.
 */
HRESULT M2DeviceIoControl(
    _In_ HANDLE hDevice,
    _In_ DWORD dwIoControlCode,
    _In_opt_ LPVOID lpInBuffer,
    _In_ DWORD nInBufferSize,
    _Out_opt_ LPVOID lpOutBuffer,
    _In_ DWORD nOutBufferSize,
    _Out_opt_ LPDWORD lpBytesReturned,
    _Inout_opt_ LPOVERLAPPED lpOverlapped);

#endif

/**
 * Retrieves file information for the specified file.
 *
 * @param hFile A handle to the file that contains the information to be
 *              retrieved. This handle should not be a pipe handle.
 * @param FileInformationClass A FILE_INFO_BY_HANDLE_CLASS enumeration value
 *                             that specifies the type of information to be
 *                             retrieved.
 * @param lpFileInformation A pointer to the buffer that receives the requested
 *                          file information.
 * @param dwBufferSize The size of the lpFileInformation buffer, in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see GetFileInformationByHandleEx.
 */
HRESULT M2GetFileInformation(
    _In_  HANDLE hFile,
    _In_  FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
    _Out_ LPVOID lpFileInformation,
    _In_  DWORD dwBufferSize);

/**
 * Sets the file information for the specified file.
 *
 * @param hFile A handle to the file for which to change information. This
 *              handle should not be a pipe handle.
 * @param FileInformationClass A FILE_INFO_BY_HANDLE_CLASS enumeration value
 *                             that specifies the type of information to be
 *                             changed.
 * @param lpFileInformation A pointer to the buffer that contains the
 *                          information to change for the specified file
 *                          information class.
 * @param dwBufferSize The size of the lpFileInformation buffer, in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see SetFileInformationByHandle.
 */
HRESULT M2SetFileInformation(
    _In_ HANDLE hFile,
    _In_ FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
    _In_ LPVOID lpFileInformation,
    _In_ DWORD dwBufferSize);

/**
 * Creates a single uninitialized object of the class associated with a
 * specified CLSID.
 *
 * @param lpszCLSID The string representation of the CLSID.
 * @param pUnkOuter If NULL, indicates that the object is not being created as
 *                  part of an aggregate. If non-NULL, pointer to the aggregate
 *                  object's IUnknown interface (the controlling IUnknown).
 * @param dwClsContext Context in which the code that manages the newly created
 *                     object will run. The values are taken from the
 *                     enumeration CLSCTX.
 * @param lpszIID A pointer to the string representation of the IID.
 * @param ppv Address of pointer variable that receives the interface pointer
 *            requested in riid. Upon successful return, *ppv contains the
 *            requested interface pointer. Upon failure, *ppv contains NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CoCreateInstance.
 */
HRESULT M2CoCreateInstance(
    _In_ LPCWSTR lpszCLSID,
    _In_opt_ LPUNKNOWN pUnkOuter,
    _In_ DWORD dwClsContext,
    _In_ LPCWSTR lpszIID,
    _Out_ LPVOID* ppv);

#endif // !_M2_WINDOWS_DOWNLEVEL_HELPERS_
