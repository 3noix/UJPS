#include "LAYERS/LayerCalculator.h"
#include "AbstractRealJoystick.h"



///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  REGISTER LAYER DIM 1
//  REGISTER LAYER DIM 2
//  CLEAR
//
//  COMPUTE LAYER
//  LAYER CHANGED
//  LAYER
//
//  DEFAULT LAYER
//  DEFAULT LAYER 1
//  DEFAULT LAYER 2
///////////////////////////////////////////////////////////////////////////////



// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
LayerCalculator::LayerCalculator() : m_layer{std::make_pair(Layers::Out,Layers::Middle)}
{
	m_layerChanged = false;
}




// REGISTER LAYER DIM 1 ///////////////////////////////////////////////////////
void LayerCalculator::registerLayerDim1(Layers::LayerDim1 layer1, AbstractRealJoystick *rj, uint rButton)
{
	// we remove the Dim1Binding which concerns layer1 if there is one
	auto islayer1 = [layer1](Dim1Binding d){return (std::get<0>(d) == layer1);};
	std::remove_if(m_dim1.begin(),m_dim1.end(),islayer1);
	
	// we add the Dim1Binding
	m_dim1.push_back(std::make_tuple(layer1,rj,rButton));
}

// REGISTER LAYER DIM 1 ///////////////////////////////////////////////////////
void LayerCalculator::registerLayerDim2(Layers::LayerDim2 layer2, AbstractRealJoystick *rj, uint rButton)
{
	// we remove the Dim2Binding which concerns layer2 if there is one
	auto islayer2 = [layer2](Dim2Binding d){return (std::get<0>(d) == layer2);};
	std::remove_if(m_dim2.begin(),m_dim2.end(),islayer2);
	
	// we add the Dim2Binding
	m_dim2.push_back(std::make_tuple(layer2,rj,rButton));
}

// CLEAR //////////////////////////////////////////////////////////////////////
void LayerCalculator::clear()
{
	m_dim1.clear();
	m_dim2.clear();
}





// COMPUTE LAYER //////////////////////////////////////////////////////////////
void LayerCalculator::computeLayer()
{
	Layers::LayerDim1 layer1 = defaultLayer1();
	Layers::LayerDim2 layer2 = defaultLayer2();
	
	for (const Dim1Binding &d : m_dim1)
	{
		AbstractRealJoystick *rj = std::get<1>(d);
		uint rButton = std::get<2>(d);
		if (rj && rj->buttonPressed(rButton))
		{
			layer1 = std::get<0>(d);
			break;
		}
	}
	
	for (const Dim2Binding &d : m_dim2)
	{
		AbstractRealJoystick *rj = std::get<1>(d);
		uint rButton = std::get<2>(d);
		if (rj && rj->buttonPressed(rButton))
		{
			layer2 = std::get<0>(d);
			break;
		}
	}
	
	Layer previousLayer = m_layer;
	m_layer = std::make_pair(layer1,layer2);
	m_layerChanged = (m_layer != previousLayer);
}

// LAYER CHANGED //////////////////////////////////////////////////////////////
bool LayerCalculator::layerChanged() const
{
	return m_layerChanged;
}

// LAYER //////////////////////////////////////////////////////////////////////
Layer LayerCalculator::layer() const
{
	return m_layer;
}







// DEFAULT LAYER //////////////////////////////////////////////////////////////
Layer LayerCalculator::defaultLayer()
{
	return std::make_pair(defaultLayer1(),defaultLayer2());
}

// DEFAULT LAYER 1 ////////////////////////////////////////////////////////////
Layers::LayerDim1 LayerCalculator::defaultLayer1()
{
	return Layers::Out;
}

// DEFAULT LAYER 2 ////////////////////////////////////////////////////////////
Layers::LayerDim2 LayerCalculator::defaultLayer2()
{
	return Layers::Middle;
}

