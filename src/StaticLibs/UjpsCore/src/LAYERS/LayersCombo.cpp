#include "LayersCombo.h"
#include "../ExceptionBadLayersCombo.h"
#include <algorithm>
#include <QStringList>


Layer OD = std::make_pair(Layers::Out,Layers::Down);
Layer OM = std::make_pair(Layers::Out,Layers::Middle);
Layer OU = std::make_pair(Layers::Out,Layers::Up);
Layer ID = std::make_pair(Layers::In,Layers::Down);
Layer IM = std::make_pair(Layers::In,Layers::Middle);
Layer IU = std::make_pair(Layers::In,Layers::Up);


///////////////////////////////////////////////////////////////////////////////
// TO STRING
// LAYERS COMBO
//  CONSTRUCTEURS
//  CONTAINS
//  TO STRING
///////////////////////////////////////////////////////////////////////////////


// TO STRING //////////////////////////////////////////////////////////////////
QString toString(Layer layer)
{
	if (layer == OM)      {return "OM";}
	else if (layer == OD) {return "OD";}
	else if (layer == OU) {return "OU";}
	else if (layer == IM) {return "IM";}
	else if (layer == ID) {return "ID";}
	else if (layer == IU) {return "IU";}
	else                  {return "Unknown";}
}






// CONSTRUCTEURS //////////////////////////////////////////////////////////////
LayersCombo::LayersCombo()
{
	m_layers.push_back(OD);
	m_layers.push_back(OM);
	m_layers.push_back(OU);
	m_layers.push_back(ID);
	m_layers.push_back(IM);
	m_layers.push_back(IU);
}

LayersCombo::LayersCombo(const std::vector<Layer> layers)
{
	m_layers = layers;
}

LayersCombo::LayersCombo(QString str)
{
	str = str.toLower();
	str.remove(' ');
	
	// we do some verification on str2
	QString str2 = str;
	str2.remove('i');
	str2.remove('o');
	str2.remove('d');
	str2.remove('m');
	str2.remove('u');
	str2.remove('|');
	if (!str2.isEmpty()) {throw ExceptionBadLayersCombo{};}
	
	for (QString &s : str.split('|',Qt::KeepEmptyParts))
	{
		bool bi = s.contains('i');
		bool bo = s.contains('o');
		bool bd = s.contains('d');
		bool bm = s.contains('m');
		bool bu = s.contains('u');
		
		if (!bi && !bo) {bi = true; bo = true;}
		if (!bd && !bm && !bu) {bd = true; bm = true; bu = true;}
		
		std::vector<Layer> temp;
		if (bo && bd) {temp.push_back(OD);}
		if (bo && bm) {temp.push_back(OM);}
		if (bo && bu) {temp.push_back(OU);}
		if (bi && bd) {temp.push_back(ID);}
		if (bi && bm) {temp.push_back(IM);}
		if (bi && bu) {temp.push_back(IU);}
		
		for (Layer layer : temp)
		{
			if (this->contains(layer)) {throw ExceptionBadLayersCombo{};}
			m_layers.push_back(layer);
		}
	}
}

// CONTAINS ///////////////////////////////////////////////////////////////////
bool LayersCombo::contains(Layer layer) const
{
	auto result = std::find(m_layers.begin(),m_layers.end(),layer);
	return (result != m_layers.end());
}

// TO STRING //////////////////////////////////////////////////////////////////
QString LayersCombo::toString() const
{
	if (m_layers.size() == 0) {return "None";}
	QStringList list;
	for (Layer layer : m_layers)
	{
		QString str;
		
		if (layer.first == Layers::Out) {str += "O";}
		else {str += "I";}
		
		if (layer.second == Layers::Down) {str += "D";}
		else if (layer.second == Layers::Middle) {str += "M";}
		else {str += "U";}
		
		list << str;
	}
	return list.join('|');
}

