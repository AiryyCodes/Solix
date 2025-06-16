
#include "Scene/Node.h"

int Node::GetNumSimilarNames(const std::string &name)
{
    int names = 0;
    for (int i = 0; i < m_Children.GetLength(); i++)
    {
        Ref<Node> node = m_Children.Get(i);
        if (node->GetName() == name)
        {
            names++;
        }
    }

    return names;
}
