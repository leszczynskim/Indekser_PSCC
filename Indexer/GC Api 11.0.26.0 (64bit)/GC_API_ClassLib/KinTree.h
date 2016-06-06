#pragma once

#include "ProgItr.h"
#include "Matrix.h"
#include <string>

#pragma pack (push, tree_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

//--------------------------- KinNode -----------------------

class KinNode
{
	public:
		KinNode()
		{
			API_VERIFY(gc_CreateEmptyNode(&ptr));
		}

		explicit KinNode(gc_kNode *node)
			: ptr(node)
		{
		}
		
		KinNode(const KinNode &that)
		{
			ptr = that.ptr;
			if (ptr)
				API_VERIFY(gc_CopyNode(ptr, &ptr));
		}

		void swap(KinNode &that)
		{
			std::swap(ptr, that.ptr);
		}

		KinNode & operator = (const KinNode &that)
		{
			swap(KinNode(that));
			return *this;
		}

		~KinNode()
		{
			if (ptr)
				gc_DeleteNode(ptr);
		}
		
		gc_kNode * operator () ()
		{
			return ptr;
		}

		const gc_kNode * operator () () const
		{
			return ptr;
		}

		bool empty() const
		{
			bool is_empty = true;
			if (ptr)
				API_VERIFY(gc_IsNodeEmpty(ptr, is_empty));
			return is_empty;
		}
		
		gc_kNodeID id() const
		{
			gc_kNodeID the_id;
			API_VERIFY(gc_GetNodeID(ptr, the_id));
			return the_id;
		}

		char *get_name(char *s) const
		{
			API_VERIFY(gc_GetNodeName(ptr, s));
			return s;
		}

		std::string &get_name(std::string &s = std::string()) const
		{
			char buf[32];
			s = get_name(buf);
			return s;
		}

		char *get_user_name(char *s) const
		{
			API_VERIFY(gc_GetNodeUserName(ptr, s));
			return s;
		}

		std::string &get_user_name(std::string &s = std::string()) const
		{
			char buf[32];
			s = get_user_name(buf);
			return s;
		}

		KinNode parent() const
		{
			gc_kNode *p = nullptr;
			API_VERIFY(gc_GetNodeParent(ptr, &p));
			return KinNode(p);
		}

		int num_children() const
		{
			int n = 0;
			API_VERIFY(gc_GetNodeChildCount(ptr, n));
			return n;
		}

		KinNode child(int ix) const
		{
			gc_kNode *p = nullptr;
			API_VERIFY(gc_GetNodeChild(ptr, ix, &p));
			return KinNode(p);
		}

		gc_AxisNodeType axis_type() const
		{
			gc_AxisNodeType type = gc_UnspecifiedAxisType;
			API_VERIFY(gc_GetAxisNodeInfo(ptr, &type, 0));
			return type;
		}

		int nom_axis() const
		{
			int axis_ix = 0;;
			API_VERIFY(gc_GetAxisNodeInfo(ptr, 0, &axis_ix));
			return axis_ix;
		}

		double axis_val() const
		{
			double val = 0.0;
			API_VERIFY(gc_GetAxisNodeVal(ptr, &val));
			return val;
		}

	private:
		gc_kNode *ptr;
};

inline KinNode &MakeTree(KinNode &tree = KinNode(nullptr))
{
	gc_kNode *temp = NULL;
	API_VERIFY(gc_MakeMDDTree(&temp));
	tree.swap(KinNode(temp));
	return tree;
}

inline KinNode &GetProgItrTree(const ProgItr &prog_itr, KinNode &tree = KinNode(nullptr))
{
	gc_kNode *temp = NULL;
	API_VERIFY(gc_GetProgItrTree(prog_itr(), &temp));
	tree.swap(KinNode(temp));
	return tree;
}

inline KinNode &GetProgItrPrevTree(const ProgItr &prog_itr, KinNode &tree = KinNode(nullptr))
{
	gc_kNode *temp = NULL;
	API_VERIFY(gc_GetProgItrPrevTree(prog_itr(), &temp));
	tree.swap(KinNode(temp));
	return tree;
}

inline KinNode &DeepCopyTree(const KinNode &src_tree, KinNode &dst_tree = KinNode(nullptr))
{
	gc_kNode *temp = NULL;
	API_VERIFY(gc_CopyTree(src_tree(), &temp));
	dst_tree.swap(KinNode(temp));
	return dst_tree;
}

inline KinNode &GetTreeNode(const KinNode &tree, gc_kNodeID id, KinNode &node = KinNode(nullptr))
{
	gc_kNode *temp = NULL;
	gc_FindNodeFromID(tree(), id, &temp);
	node.swap(KinNode(temp));
	return node;
}

inline KinNode &GetTreeNode(const KinNode &tree, const std::string &name, KinNode &node = KinNode(nullptr))
{
	gc_kNode *temp = NULL;
	gc_FindNodeFromName(tree(), name.c_str(), &temp);
	node.swap(KinNode(temp));
	return node;
}

inline Matrix &GetNodeTransform(const KinNode &from_node, const KinNode &to_node, gc_AxisCategorySet zeroed, Matrix &mx = Matrix())
{
	API_VERIFY(gc_GetNodeTransform(from_node(), to_node(), zeroed, mx[0]));
	Classify(mx);
	return mx;
}

inline Matrix &GetNodeTransform(const KinNode &from_node, const KinNode &to_node, Matrix &mx = Matrix())
{
	API_VERIFY(gc_GetNodeTransform(from_node(), to_node(), gc_AxisCategorySet(), mx[0]));
	Classify(mx);
	return mx;
}

inline Matrix &GetNodeTransform(const KinNode &tree, gc_kNodeID from_id, gc_kNodeID to_id, gc_AxisCategorySet zeroed, Matrix &mx = Matrix())
{
	GetNodeTransform(GetTreeNode(tree, from_id), GetTreeNode(tree, to_id), zeroed, mx);
	return mx;
}

inline Matrix &GetNodeTransform(const KinNode &tree, gc_kNodeID from_id, gc_kNodeID to_id, Matrix &mx = Matrix())
{
	GetNodeTransform(GetTreeNode(tree, from_id), GetTreeNode(tree, to_id), mx);
	return mx;
}

inline void SetNodePos(KinNode &tree, gc_InterpSet &interp_set, gc_AxisCategorySet zeroed, const Pt3d &pos)
{
	API_VERIFY(gc_SetNodePos(tree(), interp_set, zeroed, pos));
}

}	// end namespace GCApi

#pragma pack (pop, tree_align)						// restore struct alignment
