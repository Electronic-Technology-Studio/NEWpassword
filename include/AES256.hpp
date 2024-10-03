#pragma once
#include "include.h"

// 加密函数
void aes_encrypt(const std::vector<uint8_t>& plaintext, const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv, std::vector<uint8_t>& ciphertext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key.data(), 256, &aes_key); // 256位密钥

    ciphertext.resize(plaintext.size() + AES_BLOCK_SIZE);
    int len;
    AES_cbc_encrypt(plaintext.data(), ciphertext.data(), plaintext.size(), &aes_key, iv.data(), AES_ENCRYPT);

    // 确保输出长度是块大小的倍数
    while (ciphertext.size() % AES_BLOCK_SIZE != 0) {
        ciphertext.push_back(0);
    }
}

// 解密函数
void aes_decrypt(const std::vector<uint8_t>& ciphertext, const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv, std::vector<uint8_t>& plaintext) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key.data(), 256, &aes_key); // 256位密钥

    plaintext.resize(ciphertext.size());
    AES_cbc_encrypt(ciphertext.data(), plaintext.data(), ciphertext.size(), &aes_key, iv.data(), AES_DECRYPT);

    // 移除填充
    while (!plaintext.empty() && plaintext.back() == 0) {
        plaintext.pop_back();
    }
}