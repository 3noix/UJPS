#ifndef LAYERS_CALCULATOR
#define LAYERS_CALCULATOR


#include "Layer.h"
#include <vector>
#include <tuple>
#include <algorithm>
class AbstractRealJoystick;

using Dim1Binding = std::tuple<Layers::LayerDim1,AbstractRealJoystick*,uint>;
using Dim2Binding = std::tuple<Layers::LayerDim2,AbstractRealJoystick*,uint>;


class LayerCalculator
{
	public:
		LayerCalculator();
		~LayerCalculator() = default;
		
		void computeLayer();
		bool layerChanged() const;
		Layer layer() const;
		
		void registerLayerDim1(Layers::LayerDim1 layer1, AbstractRealJoystick *rj = nullptr, uint rButton = 0);
		void registerLayerDim2(Layers::LayerDim2 layer2, AbstractRealJoystick *rj = nullptr, uint rButton = 0);
		void clear();
		
		static Layer defaultLayer();
		
		
	private:
		static Layers::LayerDim1 defaultLayer1();
		static Layers::LayerDim2 defaultLayer2();
		
		Layer m_layer;
		bool m_layerChanged;
		
		std::vector<Dim1Binding> m_dim1;
		std::vector<Dim2Binding> m_dim2;
};


#endif

