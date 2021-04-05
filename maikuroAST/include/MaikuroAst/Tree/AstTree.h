#pragma once

#include "MaikuroAst.h"

namespace MaikuroAst::Tree {
    using namespace MaikuroAst;

    class AstTree;

    typedef std::shared_ptr<AstTree> AstTreePtr;
    typedef std::vector<AstTreePtr>  AstTreePtrVec;

    class AstTree {
     public:
        AstTree(AstNodePtr head, AstTreePtrVec children) : _head(head), _children(children) {
        }

        AstTree(AstNodePtr head) : AstTree(head, AstTreePtrVec{}) {
        }

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

        AstNodePtrVec getNodes() {
            if (_children.size() < 1) {
                return AstNodePtrVec{ _head };
            }

            AstNodePtrVec nodes = { _head };
            for (auto     child : _children) {
                for (auto n : child->getNodes()) {

                    nodes.push_back(n);
                }
            }

            return nodes;
        }

        AstNodePtr getHead() {
            return _head;
        }

        AstTreePtrVec getChildren() {
            return _children;
        }

     private:
        AstNodePtr    _head;
        AstTreePtrVec _children;
    };
}