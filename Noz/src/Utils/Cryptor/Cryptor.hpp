#pragma once

#include <string>
#include <type_traits>

namespace Noz
{
    template <typename T>
    class CryptorBase
    {
    protected:
        static const std::string s_Base64Chars;
        static std::string s_Key;
    };

    template <typename T>
    const std::string CryptorBase<T>::s_Base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/@~*.";

    template <typename T>
    std::string CryptorBase<T>::s_Key = "\\Driver\\Disk";

    class Cryptor : public CryptorBase<void>
    {

    public:

        Cryptor() = delete;

        static std::string Encrypt(const char* in, const std::string& key = s_Key)
        {
            return Base64Encode(DoXor(std::string(in), key));
        }

        template <typename buffer_type>
        static buffer_type Encrypt(const buffer_type& in, const std::string& key = s_Key)
        {
            return Base64Encode(do_xor(in, key));
        }

        static std::string Decrypt(const char* in, const std::string& key = s_Key)
        {
            return DoXor(Base64Decode(std::string(in)), key);
        }

        template <typename buffer_type>
        static buffer_type Decrypt(const buffer_type& in, const std::string& key = s_Key)
        {
            return DoXor(Base64Decode(in), key);
        }

        static void SetKey(const std::string& key) { s_Key = key; }

    private:

        static std::string DoXor(const char* data, const std::string& key)
        {
            return DoXor(std::string(data), key);
        }

        template <typename buffer_type>
        static buffer_type DoXor(const buffer_type& data, const std::string& key)
        {
            buffer_type ret(data);
            XorImpl(ret, key);
            return ret;
        }

        template <typename buffer_type>
        static void XorImpl(buffer_type& data, const std::string& key)
        {
            for (size_t i = 0; i < data.size(); ++i)
            {
                data[i] ^= key.at(i % key.size());
            }
        }

        static std::string Base64Encode(const char* in)
        {
            return Base64EncodeImpl(std::string(in));
        }

        template <typename buffer_type>
        static buffer_type Base64Encode(const buffer_type& in)
        {
            return Base64EncodeImpl(in);
        }

        template <typename buffer_type>
        static buffer_type Base64EncodeImpl(const buffer_type& in)
        {
            buffer_type ret;

            auto bytes_to_encode = in.data();
            auto in_len = in.size();

            int i = 0;
            int j = 0;
            uint8_t char_array_3[3];
            uint8_t char_array_4[4];

            while (in_len--)
            {
                char_array_3[i++] = *(bytes_to_encode++);
                if (i == 3)
                {
                    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                    char_array_4[3] = char_array_3[2] & 0x3f;

                    for (i = 0; i < 4; ++i)
                    {
                        ret.push_back(s_Base64Chars.at(char_array_4[i]));
                    }

                    i = 0;
                }
            }

            if (i)
            {
                for (j = i; j < 3; ++j)
                {
                    char_array_3[j] = '\0';
                }

                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

                for (j = 0; j < i + 1; ++j)
                {
                    ret.push_back(s_Base64Chars.at(char_array_4[j]));
                }

                while (i++ < 3)
                {
                    ret.push_back('=');
                }
            }

            return ret;
        }

        static std::string Base64Decode(const char* encoded_data)
        {
            return Base64Decode(std::string(encoded_data));
        }

        template <typename buffer_type>
        static buffer_type Base64Decode(const buffer_type& encoded_data)
        {
            buffer_type out;
            Base64DecodeImpl(encoded_data, out);
            return out;
        }

        template <typename buffer_type, typename out_type>
        static void Base64DecodeImpl(buffer_type&& encoded_data, out_type& out)
        {
            auto in_len = encoded_data.size();
            int i = 0;
            int j = 0;
            int in_ = 0;
            uint8_t char_array_4[4], char_array_3[3];

            while (in_len-- && (encoded_data[in_] != '=') && IsBase64(encoded_data[in_]))
            {
                char_array_4[i++] = encoded_data[in_]; in_++;
                if (i == 4)
                {
                    for (i = 0; i < 4; ++i)
                    {
                        char_array_4[i] = static_cast<uint8_t>(s_Base64Chars.find(char_array_4[i]));
                    }

                    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

                    for (i = 0; i < 3; ++i)
                    {
                        out.push_back(char_array_3[i]);
                    }

                    i = 0;
                }
            }

            if (i)
            {
                for (j = 0; j < i; ++j)
                {
                    char_array_4[j] = static_cast<uint8_t>(s_Base64Chars.find(char_array_4[j]));
                }

                char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

                for (j = 0; j < i - 1; ++j)
                {
                    out.push_back(char_array_3[j]);
                }
            }
        }

        static bool IsBase64(uint8_t c)
        {
            return (isalnum(c) || (c == '+') || (c == '/'));
        }

    };
}

#define NOZ_OBFUSCATE(text) ::Noz::Cryptor::Decrypt(::Noz::Cryptor::Encrypt(text)).c_str()