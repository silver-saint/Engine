#include "Layer.hpp"

namespace Engine
{
    std::string_view Layer::GetName() { return p_Name; }

    std::string_view Layer::GetName() const { return p_Name; }

    bool Layer::ShouldExit() { return m_ShouldExit; }

    void Layer::SetShouldExit(bool value) { m_ShouldExit = value; }
};// namespace Engine