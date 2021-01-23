﻿/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.Core.h
 * PURPOSE:   Windows Core Definition for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MILE_WINDOWS_CORE
#define MILE_WINDOWS_CORE

#if (defined(__cplusplus) && __cplusplus >= 201703L)
#elif (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
#else
#error "[Mile] You should use a C++ compiler with the C++17 standard."
#endif

#include <Windows.h>

#include <string>

namespace Mile
{
    /**
     * @brief Disables C++ class copy construction.
    */
    class DisableCopyConstruction
    {
    protected:
        DisableCopyConstruction() = default;
        ~DisableCopyConstruction() = default;

    private:
        DisableCopyConstruction(
            const DisableCopyConstruction&) = delete;
        DisableCopyConstruction& operator=(
            const DisableCopyConstruction&) = delete;
    };

    /**
     * @brief Disables C++ class move construction.
    */
    class DisableMoveConstruction
    {
    protected:
        DisableMoveConstruction() = default;
        ~DisableMoveConstruction() = default;

    private:
        DisableMoveConstruction(
            const DisableMoveConstruction&&) = delete;
        DisableMoveConstruction& operator=(
            const DisableMoveConstruction&&) = delete;
    };

    /**
     * @brief A type representing an HRESULT error code.
    */
    class HResult
    {
    public:

        /**
         * @brief The HRESULT error code represented by the HResult object.
        */
        HRESULT Value{ S_OK };

    public:

        /**
         * @brief Initializes a new instance of the HResult object.
         * @return A new instance of the HResult object.
        */
        constexpr HResult() noexcept = default;

        /**
         * @brief Initializes a new instance of the HResult object by an
         *        HRESULT code.
         * @param Value An HRESULT code that initializes the HResult object.
         * @return A new instance of the HResult object.
        */
        constexpr HResult(
            _In_ HRESULT const Value) noexcept : Value(Value)
        {
        }

        /**
         * @brief Initializes a new instance of the HResult object by a system
         *        error code.
         * @param Code The system error code.
         * @return A new instance of the HResult object.
        */
        static HResult FromWin32(
            _In_ DWORD Code) noexcept
        {
            return HResult(::HRESULT_FROM_WIN32(Code));
        }

        /**
         * @brief Initializes a new instance of the HResult object by the
         *        calling thread's last-error code.
         * @return A new instance of the HResult object.
        */
        static HResult FromLastError() noexcept
        {
            return FromWin32(::GetLastError());
        }

    public:

        /**
         * @brief Retrieves the HRESULT error code for the error represented by
         *        the HResult object.
         * @return An HRESULT error code.
        */
        constexpr operator HRESULT() const noexcept
        {
            return this->Value;
        }

        /**
         * @brief Retrieves the message for the error represented by the
         *        HResult object.
         * @return A std::wstring containing the error messsage.
        */
        std::wstring ToMessage() const noexcept
        {
            std::wstring Message{ L"Failed to get formatted message." };

            LPWSTR RawMessage = nullptr;
            DWORD RawMessageSize = ::FormatMessageW(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                nullptr,
                this->Value,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                reinterpret_cast<LPTSTR>(&RawMessage),
                0,
                nullptr);
            if (RawMessageSize)
            {
                Message = std::wstring(RawMessage, RawMessageSize);

                ::LocalFree(RawMessage);
            }

            return Message;
        }
    };

    /**
     * @brief Wraps the Windows heap memory manager.
    */
    class HeapMemory
    {
    public:

        /**
         * @brief Allocates a block of memory from the default heap of the
         *        calling process. The allocated memory will be initialized to
         *        zero. The allocated memory is not movable.
         * @param Size The number of bytes to be allocated.
         * @return If the function succeeds, the return value is a pointer to
         *         the allocated memory block. If the function fails, the
         *         return value is nullptr.
        */
        static LPVOID Allocate(
            _In_ SIZE_T Size) noexcept
        {
            return ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
        }

        /**
         * @brief Reallocates a block of memory from the default heap of the
         *        calling process. If the reallocation request is for a larger
         *        size, the additional region of memory beyond the original
         *        size be initialized to zero. This function enables you to
         *        resize a memory block and change other memory block
         *        properties. The allocated memory is not movable.
         * @param Block A pointer to the block of memory that the function
         *              reallocates. This pointer is returned by an earlier
         *              call to Allocate and Reallocate method.
         * @param Size The new size of the memory block, in bytes. A memory
         *             block's size can be increased or decreased by using this
         *             function.
         * @return If the function succeeds, the return value is a pointer to
         *         the reallocated memory block. If the function fails, the
         *         return value is nullptr.
        */
        static LPVOID Reallocate(
            _In_ PVOID Block,
            _In_ SIZE_T Size) noexcept
        {
            return ::HeapReAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, Block, Size);
        }

        /**
         * @brief Frees a memory block allocated from a heap by the Allocate or
         *        Reallocate method.
         * @param Block A pointer to the memory block to be freed. This pointer
         *              is returned by the Allocate or Reallocate method. If
         *              this pointer is nullptr, the behavior is undefined.
         * @return If the function succeeds, the return value is nonzero. If
         *         the function fails, the return value is zero. An application
         *         can call GetLastError for extended error information.
        */
        static BOOL Free(
            _In_ LPVOID Block) noexcept
        {
            return ::HeapFree(::GetProcessHeap(), 0, Block);
        }
    };

    /**
     * @brief Wraps a critical section object.
    */
    class CriticalSection : DisableCopyConstruction, DisableMoveConstruction
    {
    public:

        /**
         * @brief Initializes a critical section object.
         * @param lpCriticalSection A pointer to the critical section object.
         * @remark For more information, see InitializeCriticalSection.
         */
        static void Initialize(
            _Out_ LPCRITICAL_SECTION lpCriticalSection) noexcept
        {
            ::InitializeCriticalSection(lpCriticalSection);
        }

        /**
         * @brief Releases all resources used by an unowned critical section
         *        object.
         * @param lpCriticalSection A pointer to the critical section object.
         * @remark For more information, see DeleteCriticalSection.
         */
        static void Delete(
            _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept
        {
            ::DeleteCriticalSection(lpCriticalSection);
        }

        /**
         * @brief Waits for ownership of the specified critical section object.
         *        The function returns when the calling thread is granted
         *        ownership.
         * @param lpCriticalSection A pointer to the critical section object.
         * @remark For more information, see EnterCriticalSection.
         */
        static void Enter(
            _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept
        {
            ::EnterCriticalSection(lpCriticalSection);
        }

        /**
         * @brief Attempts to enter a critical section without blocking. If the
         *        call is successful, the calling thread takes ownership of the
         *        critical section.
         * @param lpCriticalSection A pointer to the critical section object.
         * @return If the critical section is successfully entered or the
         *         current thread already owns the critical section, the return
         *         value is true. If another thread already owns the critical
         *         section, the return value is false.
         * @remark For more information, see TryEnterCriticalSection.
         */
        static bool TryEnter(
            _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept
        {
            return FALSE != ::TryEnterCriticalSection(lpCriticalSection);
        }

        /**
         * @brief Releases ownership of the specified critical section object.
         * @param lpCriticalSection A pointer to the critical section object.
         * @remark For more information, see LeaveCriticalSection.
         */
        static void Leave(
            _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept
        {
            ::LeaveCriticalSection(lpCriticalSection);
        }

    private:

        /**
         * @brief The raw critical section object.
        */
        CRITICAL_SECTION m_RawObject;

    public:

        /**
         * @brief Initializes the critical section object.
        */
        CriticalSection() noexcept
        {
            Initialize(&this->m_RawObject);
        }

        /**
         * @brief Releases all resources used by the critical section object.
        */
        ~CriticalSection() noexcept
        {
            Delete(&this->m_RawObject);
        }

        /**
         * @brief Waits for ownership of the critical section object. The
         *        function returns when the calling thread is granted ownership.
        */
        void Lock() noexcept
        {
            Enter(&this->m_RawObject);
        }

        /**
         * @brief Attempts to enter the critical section without blocking. If
         *        the call is successful, the calling thread takes ownership of
         *        the critical section.
         * @return If the critical section is successfully entered or the
         *         current thread already owns the critical section, the return
         *         value is true. If another thread already owns the critical
         *         section, the return value is false.
        */
        bool TryLock() noexcept
        {
            return TryEnter(&this->m_RawObject);
        }

        /**
         * @brief Releases ownership of the critical section object.
        */
        void Unlock() noexcept
        {
            Leave(&this->m_RawObject);
        }
    };

    /**
     * @brief Provides automatic locking and unlocking of a critical section.
    */
    class AutoCriticalSectionLock
    {
    private:

        /**
         * @brief The critical section object.
        */
        CriticalSection& m_Object;

    public:

        /**
         * @brief Lock the critical section object.
         * @param Object The critical section object.
        */
        explicit AutoCriticalSectionLock(
            CriticalSection& Object) noexcept :
            m_Object(Object)
        {
            this->m_Object.Lock();
        }

        /**
         * @brief Unlock the critical section object.
        */
        ~AutoCriticalSectionLock() noexcept
        {
            this->m_Object.Unlock();
        }
    };

    /**
     * @brief Provides automatic trying to lock and unlocking of a critical
     *        section.
    */
    class AutoCriticalSectionTryLock
    {
    private:

        /**
         * @brief The critical section object.
        */
        CriticalSection& m_Object;

        /**
         * @brief The lock status.
        */
        bool m_IsLocked;

    public:

        /**
         * @brief Try to lock the critical section object.
         * @param Object The critical section object.
        */
        explicit AutoCriticalSectionTryLock(
            CriticalSection& Object) noexcept :
            m_Object(Object)
        {
            this->m_IsLocked = this->m_Object.TryLock();
        }

        /**
         * @brief Try to unlock the critical section object.
        */
        ~AutoCriticalSectionTryLock() noexcept
        {
            if (this->m_IsLocked)
            {
                this->m_Object.Unlock();
            }
        }

        /**
         * @brief Check the lock status.
         * @return The lock status.
        */
        bool IsLocked() const
        {
            return this->m_IsLocked;
        }
    };

    /**
     * @brief Wraps a slim reader/writer (SRW) lock.
    */
    class SRWLock : DisableCopyConstruction, DisableMoveConstruction
    {
    public:

        /**
         * @brief Initialize a slim reader/writer (SRW) lock.
         * @param SRWLock A pointer to the SRW lock.
         * @remark For more information, see InitializeSRWLock.
         */
        static void Initialize(
            _Out_ PSRWLOCK SRWLock) noexcept
        {
            ::InitializeSRWLock(SRWLock);
        }

        /**
         * @brief Acquires a slim reader/writer (SRW) lock in exclusive mode.
         * @param SRWLock A pointer to the SRW lock.
         * @remark For more information, see AcquireSRWLockExclusive.
         */
        static void AcquireExclusive(
            _Inout_ PSRWLOCK SRWLock) noexcept
        {
            ::AcquireSRWLockExclusive(SRWLock);
        }

        /**
         * @brief Attempts to acquire a slim reader/writer (SRW) lock in
         *        exclusive mode. If the call is successful, the calling thread
         *        takes ownership of the lock.
         * @param SRWLock A pointer to the SRW lock.
         * @return If the lock is successfully acquired, the return value is
         *         true. If the current thread could not acquire the lock, the
         *         return value is false.
         * @remark For more information, see TryAcquireSRWLockExclusive.
         */
        static bool TryAcquireExclusive(
            _Inout_ PSRWLOCK SRWLock) noexcept
        {
            return FALSE != ::TryAcquireSRWLockExclusive(SRWLock);
        }

        /**
         * @brief Releases a slim reader/writer (SRW) lock that was acquired in
         *        exclusive mode.
         *
         * @param SRWLock A pointer to the SRW lock.
         * @remark For more information, see ReleaseSRWLockExclusive.
         */
        static void ReleaseExclusive(
            _Inout_ PSRWLOCK SRWLock) noexcept
        {
            ::ReleaseSRWLockExclusive(SRWLock);
        }

        /**
         * @brief Acquires a slim reader/writer (SRW) lock in shared mode.
         * @param SRWLock A pointer to the SRW lock.
         * @remark For more information, see AcquireSRWLockShared.
         */
        static void AcquireShared(
            _Inout_ PSRWLOCK SRWLock) noexcept
        {
            ::AcquireSRWLockShared(SRWLock);
        }

        /**
         * @brief Attempts to acquire a slim reader/writer (SRW) lock in shared
         *        mode. If the call is successful, the calling thread takes
         *        ownership of the lock.
         * @param SRWLock A pointer to the SRW lock.
         * @return If the lock is successfully acquired, the return value is
         *         true. If the current thread could not acquire the lock, the
         *         return value is false.
         * @remark For more information, see TryAcquireSRWLockShared.
         */
        static bool TryAcquireShared(
            _Inout_ PSRWLOCK SRWLock) noexcept
        {
            return FALSE != ::TryAcquireSRWLockShared(SRWLock);
        }

        /**
         * @brief Releases a slim reader/writer (SRW) lock that was acquired in
         *        shared mode.
         * @param SRWLock A pointer to the SRW lock.
         * @remark For more information, see ReleaseSRWLockShared.
         */
        static void ReleaseShared(
            _Inout_ PSRWLOCK SRWLock) noexcept
        {
            ::ReleaseSRWLockShared(SRWLock);
        }

    private:

        /**
         * @brief The raw slim reader/writer (SRW) lock object.
        */
        SRWLOCK m_RawObject;

    public:

        /**
         * @brief Initialize the slim reader/writer (SRW) lock.
        */
        SRWLock() noexcept
        {
            Initialize(&this->m_RawObject);
        }

        /**
         * @brief Acquires the slim reader/writer (SRW) lock in exclusive mode.
        */
        void LockExclusive() noexcept
        {
            AcquireExclusive(&this->m_RawObject);
        }

        /**
         * @brief Attempts to acquire the slim reader/writer (SRW) lock in
         *        exclusive mode. If the call is successful, the calling thread
         *        takes ownership of the lock.
         * @return If the lock is successfully acquired, the return value is
         *         true. If the current thread could not acquire the lock, the
         *         return value is false.
        */
        bool TryLockExclusive() noexcept
        {
            return TryAcquireExclusive(&this->m_RawObject);
        }

        /**
         * @brief Releases the slim reader/writer (SRW) lock that was acquired
         *        in exclusive mode.
        */
        void UnlockExclusive() noexcept
        {
            ReleaseExclusive(&this->m_RawObject);
        }

        /**
         * @brief Acquires the slim reader/writer (SRW) lock in shared mode.
        */
        void LockShared() noexcept
        {
            AcquireShared(&this->m_RawObject);
        }

        /**
         * @brief Attempts to acquire the slim reader/writer (SRW) lock in
         *        shared mode. If the call is successful, the calling thread
         *        takes ownership of the lock.
         * @return If the lock is successfully acquired, the return value is
         *         true. If the current thread could not acquire the lock, the
         *         return value is false.
        */
        bool TryLockShared() noexcept
        {
            return TryAcquireShared(&this->m_RawObject);
        }

        /**
         * @brief Releases the slim reader/writer (SRW) lock that was acquired
         *        in shared mode.
        */
        void UnlockShared() noexcept
        {
            ReleaseShared(&this->m_RawObject);
        }
    };
}


#endif // !MILE_WINDOWS_CORE