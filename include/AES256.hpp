#pragma once
#include "include.h"

// ���ܺ���
void aes_encrypt(const std::vector<uint8_t>& plaintext, const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv, std::vector<uint8_t>& ciphertext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key.data(), 256, &aes_key); // 256λ��Կ

    ciphertext.resize(plaintext.size() + AES_BLOCK_SIZE);
    int len;
    AES_cbc_encrypt(plaintext.data(), ciphertext.data(), plaintext.size(), &aes_key, iv.data(), AES_ENCRYPT);

    // ȷ����������ǿ��С�ı���
    while (ciphertext.size() % AES_BLOCK_SIZE != 0) {
        ciphertext.push_back(0);
    }
}

// ���ܺ���
void aes_decrypt(const std::vector<uint8_t>& ciphertext, const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv, std::vector<uint8_t>& plaintext) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key.data(), 256, &aes_key); // 256λ��Կ

    plaintext.resize(ciphertext.size());
    AES_cbc_encrypt(ciphertext.data(), plaintext.data(), ciphertext.size(), &aes_key, iv.data(), AES_DECRYPT);

    // �Ƴ����
    while (!plaintext.empty() && plaintext.back() == 0) {
        plaintext.pop_back();
    }
}