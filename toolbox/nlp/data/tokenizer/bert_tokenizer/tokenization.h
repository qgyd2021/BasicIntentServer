//
// Created by tianx on 2022/12/8.
//
#ifndef BERT_TOKENIZATION_H
#define BERT_TOKENIZATION_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

namespace nlp {

    void load_vocab(const char *vocab_file, std::unordered_map<std::string, uint64_t> *vocab);
    bool _is_whitespace(int c);
    bool _is_control(int c);
    bool _is_punctuation(int cp);
    class BasicTokenizer {
    public:
        explicit BasicTokenizer(bool do_lower_case = true) : do_lower_case(do_lower_case) {}
        BasicTokenizer(const BasicTokenizer &other) = delete;
        virtual ~BasicTokenizer() = default;
        void tokenize(const char *text, std::vector<std::string> *output_tokens, size_t max_length);

    private:
        const bool do_lower_case;
        inline static bool _is_chinese_char(int cp);
    };

    class WordpieceTokenizer {
    public:
        explicit WordpieceTokenizer(
                std::unordered_map<std::string, uint64_t> *vocab,
                std::string unk_token = "[UNK]",
                int max_input_chars_per_word = 200
        ) : vocab(vocab), unk_token(unk_token), max_input_chars_per_word(max_input_chars_per_word) {}

        WordpieceTokenizer(const WordpieceTokenizer &other) = delete;

        virtual ~WordpieceTokenizer() = default;

        void tokenize(const std::string &text, std::vector<std::string> *output_tokens);

    private:
        const std::unordered_map<std::string, uint64_t> *vocab;
        const std::string unk_token;
        const int max_input_chars_per_word;
    };

    class FullTokenizer {
    public:
        explicit FullTokenizer(const char *vocab_file, bool do_lower_case = true) {
            vocab = new std::unordered_map<std::string, uint64_t>();
            load_vocab(vocab_file, vocab);

            basic_tokenizer = new BasicTokenizer(do_lower_case);
            wordpiece_tokenizer = new WordpieceTokenizer(vocab);
        }

        FullTokenizer(const FullTokenizer &other) = delete;

        virtual ~FullTokenizer() {
            delete wordpiece_tokenizer;
            delete basic_tokenizer;
            delete vocab;
        }

        void tokenize(const char *text, std::vector<std::string> *output_tokens, size_t max_length);

        inline uint64_t convert_token_to_id(const std::string &token) {
            auto item = vocab->find(token);
            if (item == vocab->end()) {
                std::cerr << "vocab missing key: " << token << std::endl;
                return 0;
            } else {
                return item->second;
            }
        }

        void convert_tokens_to_ids(const std::vector<std::string> &tokens, uint64_t *ids);

    private:
        std::unordered_map<std::string, uint64_t> *vocab;
        BasicTokenizer *basic_tokenizer;
        WordpieceTokenizer *wordpiece_tokenizer;
    };

}

#endif //BERT_TOKENIZATION_H
