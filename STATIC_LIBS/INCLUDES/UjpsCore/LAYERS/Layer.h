#ifndef LAYER
#define LAYER


#include <utility>
#include <QString>


namespace Layers
{
	enum LayerDim1 {Out, In};
	enum LayerDim2 {Down, Middle, Up};
}

using Layer = std::pair<Layers::LayerDim1,Layers::LayerDim2>;
QString toString(Layer layer);


#endif

