#pragma once

#include "Core/Base.h"
#include "Scene/Node.h"
#include <string>

namespace Widget
{
void Button(const std::string &label);

void NodeButton(Ref<Node> node);
} // namespace Widget
