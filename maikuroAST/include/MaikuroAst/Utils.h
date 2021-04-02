#pragma once

#include "common.h"
#include "Token.h"

namespace MaikuroAst {
    using std::string;
    using std::shared_ptr;
    using std::vector;

    class Utils {
     public:
        template<typename T>
        static vector<shared_ptr<Token>> getTokens(vector<shared_ptr<T>> nodes) {
            vector<shared_ptr<Token>> tokens;

            for (const auto& node : nodes) {
                if (!node) { continue; }

                Token::mergeTokens(&tokens, node->getTokens());
            }

            return tokens;
        }

        template<typename T>
        static string nodesToString(vector<shared_ptr<T>> nodes) {
            string    out;
            for (auto node : nodes) {
                out += node->toString() + "\n";
            }

            return out;
        }

        template<typename Node, typename... _Args>
        static shared_ptr<Node> create(_Args&& ... __args) {
            typedef typename std::remove_const<Node>::type _Tp_nc;
            return std::allocate_shared<Node>(
                std::allocator<_Tp_nc>(),
                std::forward<_Args>(__args)...
            );
        }

        template<typename T, typename C>
        static vector<shared_ptr<T>> create(vector<C> contexts) {
            vector<shared_ptr<T>> result;
            for (auto             ctx : contexts) {
                result.push_back(create<T>(ctx));
            }

            return result;
        }
    };
}