#pragma once

#include <types.hpp>

namespace sead {
    template <typename T>
    class SafeStringBase {
    public:
        SafeStringBase() : mString(&cNullChar) {

        }

        SafeStringBase(const T* pStr) : mString(pStr) {

        }

        virtual ~SafeStringBase() = default;
        virtual void assureTerminationImpl_() const {

        }
        
        virtual SafeStringBase<T>& operator=(const SafeStringBase<T> &);
        
        const T* mString;       // 0x0

        static const T cNullChar;
    };

    template <typename T>
    class BufferedSafeStringBase : public SafeStringBase<T> {
    public:
        BufferedSafeStringBase(T* pBuf, s32 size) {
            mBufferSize = size;

            if (size <= 0) {
                mString = nullptr;
                mBufferSize = 0;
            }
            else {
                this->assureTerminationImpl_();
            }
        }

        T* getString() {
            return const_cast<T*>(mString);
        }

        void clear() {
            getString()[0] = cNullChar;
        }

        ~BufferedSafeStringBase() override = default;
        void assureTerminationImpl_() const override;
        BufferedSafeStringBase<T>& operator=(const SafeStringBase<T> &);

        s32 mBufferSize;            // 0x10
    };

    template<typename T, s32 Len>
    class FixedSafeStringBase : public BufferedSafeStringBase<T> {
    public:
        FixedSafeStringBase() : BufferedSafeStringBase<T>(mBuffer, Len) {
            clear();
        }

        virtual FixedSafeStringBase& operator=(const SafeStringBase<T> &);

        T mBuffer[Len]; 
    };

    /* commonly used types for easy use */
    typedef SafeStringBase<char> SafeString;
    typedef BufferedSafeStringBase<char> BufferedSafeString;
}
