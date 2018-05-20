 /*******************************
 * Copyright (c) <2007>, <Bruce Campbell> All rights reserved. Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  *  
 * Bruce B Campbell 07 08 2014  *
 ********************************/
#ifndef __kl_alorithm_paramters__
#define __kl_alorithm_paramters__

#include <string>
#include <map>
#include <ostream>
#include <fstream>
#include "kl_matrix.h"
using namespace std;

//bbcrevisit under major construction.

enum klAlgorithmParameterType { klIntType=1, klDoubleType=2, klStringType=3, klDoubleVectorType=4, klDoubleMatrixType=5};


class klAlgorithmParameter
{
public:

	klAlgorithmParameter()
	{
	}

	klAlgorithmParameter(string name, __int64_t intValue) : _name(name)
	{
		ip = intValue;
		_parameterType= klIntType;
	}

	klAlgorithmParameter(string name, double dValue) : _name(name)
	{
		dp = dValue;
		_parameterType= klDoubleType;
	}

	klAlgorithmParameter(string name, string sValue) : _name(name)
	{
		sp = sValue;
		_parameterType= klDoubleType;
	}

	klAlgorithmParameter(string name, klVector<double> kldv) : _name(name)
	{
		dvp=kldv;
		_parameterType= klDoubleVectorType;
	}

	klAlgorithmParameter(string name, klMatrix<double> kldm) : _name(name)
	{
		dmp=kldm;
		_parameterType= klDoubleMatrixType;
	}
	
	void setDescription(string descrption)
	{
		_description= descrption;
	}

	string getStringValue()
	{
		if( _parameterType != klStringType)
			throw klError(_name + "is not a klAlgorithmParameterType::klStringType");
		
		string value = sp;
		return value;
	}

	double getDoubleValue()
	{
		if( _parameterType != klDoubleType)
			throw klError(_name + "is not a klAlgorithmParameterType::klDoubleType");
		double value =dp;
		return value;
	}

	__int64_t getIntValue()
	{
		if( _parameterType != klIntType)
			throw klError(_name + "is not a klAlgorithmParameterType::klIntType");
		double value =ip;
		return value;
	}

	klVector<double> getDoubleVectorValue()
	{
		if( _parameterType != klDoubleVectorType)
			throw klError(_name + "is not a klAlgorithmParameterType::klDoubleVectorType");
	
		klVector<double> value =dvp;

		return value;
	}

	klMatrix<double> getDoubleMatrixValue()
	{
		if( _parameterType != klDoubleMatrixType)
			throw klError(_name + "is not a klAlgorithmParameterType::klDoubleMatrixType");

		klMatrix<double> value =dmp;

		return value;
	}

	klAlgorithmParameterType getType()
	{
		return _parameterType;
	}

	string getName()
	{
		return _name;
	}
	
	string getDescription()
	{
		return _description;
	}

	void serialize(ostream& str)
	{
		switch(this->getType())
			{
			case klDoubleMatrixType :
				{
					str<<"klAlgorithmParameterType::klDoubleMatrixTypeStartToken"<<endl;
					str<<this->getDoubleMatrixValue()<<endl;
					str<<"klAlgorithmParameterType::klDoubleMatrixTypeEndToken"<<endl;
					
					break;
				}
			case klDoubleType :
				{					
					str<<"klAlgorithmParameterType::klDoubleTypeStartToken"<<endl;
					str<<this->getDoubleValue()<<endl;
					str<<"klAlgorithmParameterType::klDoubleTypeEndToken"<<endl;
					break;
				}
			case klDoubleVectorType :
				{
					str<<"klAlgorithmParameterType::klDoubleVectorTypeStartToken"<<endl;
					str<<this->getDoubleVectorValue()<<endl;
					str<<"klAlgorithmParameterType::klDoubleVectorTypeEndToken"<<endl;
					break;
				}
			case klIntType :
				{
					str<<"klAlgorithmParameterType::klIntTypeStartToken"<<endl;
					str<<this->getIntValue()<<endl;
					str<<"klAlgorithmParameterType::klIntTypeEndToken"<<endl;
					break;
				}
			case klStringType :
				{
					str<<"klAlgorithmParameterType::klStringTypeStartToken"<<endl;
					str<<this->getStringValue()<<endl;
					str<<"klAlgorithmParameterType::klStringTypeEndToken"<<endl;
					break;
				}
			}	
	}

private:
	
	string _name;
	string _description;
	klAlgorithmParameterType _parameterType;
	
	int ip;
	string sp;
	double dp;
	klVector<double> dvp;
	klMatrix<double>  dmp;
};

typedef std::map<std::string, std::map<std::string, klAlgorithmParameter> >::iterator algorithmParameter_itertator;

//This class is derived from if necessary
class klAlgorithmParameterContainer
{
public:

	klAlgorithmParameterContainer()
	{
	}

	void addIntParameter(string name, __int64_t value)
	{
		klAlgorithmParameter parameter(name,value);		
		parameterMap[name] = parameter;
	}

	void addDoubleParameter(string name, double value)
	{
		klAlgorithmParameter parameter(name,value);		
		parameterMap[name] = parameter;
	}

	void addStringParameter(string name, string value)
	{
		klAlgorithmParameter parameter(name,value);		
		parameterMap[name] = parameter;
	}

	void addDoubleVectorParameter(string name, klVector<double> value)
	{
		klAlgorithmParameter parameter(name,value);		
		parameterMap[name] = parameter;
	}

	void addDoubleMatrixParameter(string name, klMatrix<double> value)
	{
		klAlgorithmParameter parameter(name,value);		
		parameterMap[name] = parameter;
	}

	void add(klAlgorithmParameter algorithmParameter)
	{ 
		string name = algorithmParameter.getName();

		std::pair<string ,klAlgorithmParameter> kvp;

		parameterMap[name]=algorithmParameter;
	}

	virtual void describeAlgorithm(ostream& str)
	{
		str<<"No description implemented"<<endl;
	}
			
	void describeAlgorithmParameters(ostream& str)
	{

		for(map<string,klAlgorithmParameter>::iterator iterator = parameterMap.begin(); iterator != parameterMap.end(); iterator++)
		{
			string key;
			klAlgorithmParameter value;

			key = iterator->first;
			value = iterator->second;
			str<<key<<"  : TYPE = "<<value.getType()<<" Description = "<<value.getDescription()<<endl;


		}
	}
	
	klAlgorithmParameter getParameter(string parameter)
	{
		return parameterMap[parameter];
	}

	void setParameter(klAlgorithmParameter parameterValue)
	{
		parameterMap[parameterValue.getName()]= parameterValue;
	}

	void serialize(string fileName)
	{		
		std::ofstream fileostream(fileName.c_str() );
		serialize(fileostream);
	}

	//This is a very basic serializer.  It is not performant for large matrices.
	void serialize(ostream & str)
	{
		time_t time_of_day;
		struct tm *tm_buf;
		time_of_day = time( NULL );
		tm_buf=localtime(&time_of_day);
		char* serializationDateTime = new char[1024];
		sprintf(serializationDateTime,"%d_%d_%d_%d_%d",tm_buf->tm_mon+1,tm_buf->tm_mday+1,tm_buf->tm_hour+1,tm_buf->tm_min+1,tm_buf->tm_sec+1);

		str<<"klDateTimeStartToken"<<endl;
		str<<serializationDateTime<<endl;
		str<<"klDateTimeEndToken"<<endl;
						
		string AlgorithmDescription;
		stringstream ss(AlgorithmDescription);
		describeAlgorithm(ss);
		str<<"klAlgorithmDescriptionStartToken"<<endl;
		str<<ss.str()<<endl; 
		typedef map<string,klAlgorithmParameter> algoMap;
		
		for(algoMap::iterator i= parameterMap.begin(); i != parameterMap.end(); i++)
		{
			string key;
			klAlgorithmParameter value;

			key = i->first;
			value = i->second;
			
			str<<"klAlgorithmParameterNameStartToken"<<endl<<key<<endl<<"klAlgorithmParameterNameEndToken"<<endl;
			str<<"klAlgorithmParameterTypeStartToken"<<endl<<value.getType()<<endl<<"klAlgorithmParameterTypeEndToken"<<endl;
			str<<"klAlgorithmParameterDescriptionStartToken"<<endl<<value.getDescription()<<endl<<"klAlgorithmParameterDescriptionEndToken"<<endl;
		
			value.serialize(str);			
		}
		str.flush();
	}

protected:
	map<string,klAlgorithmParameter> parameterMap;

};

#endif //__kl_alorithm_paramters__


