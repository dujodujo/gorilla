#include "ParamLoader.h"

ParamLoader* ParamLoader::get_instance() {
	static ParamLoader instance;
	return &instance;
}