#include"screenio.hpp"
#include"renderer.hpp"
#include"renderee.hpp"

namespace gol
{
    void Renderer::renderAll()
    {
        for(IRenderee* ree : renderees)
        {
            if(ree->needRender()) ree->render();
        }

        return;
    }

    void Renderer::addRenderee(IRenderee* renderee)
    {
        renderees.push_back(renderee);

        return;
    }
}
