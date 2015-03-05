struct Vector
{
	float x;
	float y;
	float z;
};

struct Color
{
	float r;
	float g;
	float b;
	float a;
};

template <typename T>
struct LinkedList
{
	T *data;
	LinkedList *next;
};