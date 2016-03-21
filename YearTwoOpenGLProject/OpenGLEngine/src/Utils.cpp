#include "Utils.h"

Application *GetApplication(Application * _application) {
	static Application * application = nullptr;

	if (_application != nullptr)
	{
		application = _application;
	}

	return application;
}

uint GL::SizeOf(Primitive primitiveType) {
	switch (primitiveType)
	{
		case GL::Primitive::Double:
			return sizeof(double);
		case GL::Primitive::Float:
			return sizeof(float);
		case GL::Primitive::Int:
			return sizeof(int);
		case GL::Primitive::UInt:
			return sizeof(uint);
		case GL::Primitive::Short:
			return sizeof(short);
		case GL::Primitive::Byte:
			return sizeof(char);
		case GL::Primitive::UByte:
			return sizeof(uchar);
	}
}