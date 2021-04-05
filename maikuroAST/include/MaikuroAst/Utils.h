#pragma once

#include "common.h"
#include "Token.h"

namespace MaikuroAst {

    class Utils {
     public:
        template<typename T>
        static std::vector<std::shared_ptr < Token>> getTokens(
        std::vector<std::shared_ptr<T>> nodes
        ) {
            std::vector<std::shared_ptr < Token>>
            tokens;

            for (const auto& node : nodes) {
                if (!node) { continue; }

                Token::mergeTokens(&tokens, node->getTokens());
            }

            return tokens;
        }

        template<typename T>
        static std::string nodesToString(std::vector<std::shared_ptr<T>> nodes) {
            std::string out;
            for (auto   node : nodes) {
                out += node->toString() + "\n";
            }

            return out;
        }

        template<typename Node, typename... _Args>
        static std::shared_ptr<Node> create(_Args&& ... __args) {
            typedef typename std::remove_const<Node>::type _Tp_nc;
            return std::allocate_shared<Node>(
                std::allocator<_Tp_nc>(),
                std::forward<_Args>(__args)...
            );
        }

        template<typename T, typename C>
        static std::vector<std::shared_ptr < T>> create(
        std::vector<C> contexts
        ) {
            std::vector<std::shared_ptr<T>>
            result;
            for (auto ctx : contexts) {
                result.push_back(create<T>(ctx));
            }

            return result;
        }
    };
}