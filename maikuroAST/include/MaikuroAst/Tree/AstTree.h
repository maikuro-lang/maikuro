#pragma once

#include "MaikuroAst.h"

namespace MaikuroAst::Tree {
    using namespace MaikuroAst;

    class AstTree;
    typedef shared_ptr<AstTree> AstTreePtr;
    typedef vector<AstTreePtr> AstTreePtrVec;

    class AstTree {
     public:
        AstTree(AstNodePtr head, AstTreePtrVec children) : _head(head), _children(children) {}
        AstTree(AstNodePtr head) : AstTree(head, AstTreePtrVec{}) {}
        AstTree(AstNodePtr head, AstTreePtr children) : AstTree(head) {
            add(children);
        }

        void add(AstTreePtr tree) {
            _children.push_back(tree);
        }

        void add(AstTreePtrVec trees) {
            for (auto tree : trees) {
                add(tree);
            }
        }

        void add(AstNodePtr node) {
            add(std::make_shared<AstTree>(node));
        }

        void add(AstNodePtrVec nodes) {
            for (auto node : nodes) {
                add(node);
            }
        }

        AstNodePtr getHead() {
            return _head;
        }

        AstTreePtrVec getChildren() {
            return _children;
        }
     private:
        AstNodePtr _head;
        AstTreePtrVec _children;
    };
}