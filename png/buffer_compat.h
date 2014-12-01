#include <node.h>
#include <node_buffer.h>

using namespace node;

char *BufferData(node::Buffer *b) {
	return b->data();
}