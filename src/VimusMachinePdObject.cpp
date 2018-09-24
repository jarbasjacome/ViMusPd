/**
 * Copyright 2007-2014 Jarbas Jácome
 *
 * This file is part of ViMus.
 *
 * ViMus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ViMus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ViMus.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "VimusMachinePdObject.h"

using namespace std;

/**
 * VimusMachinePdObject default constructor.
 */
VimusMachinePdObject::VimusMachinePdObject(const std::string& nome,
        int pinosEntrada, int tiposPinosEntrada[],
        int pinosSaida, int tiposPinosSaida[],
        int indice, PdMaquina * pd)
//FAZER: colocar uma referência para o patch
//que o objeto pertence dentro do Pd
{
    VimusMachineObject::initObject();

    this->label = nome;

    this->indiceNoPd = indice;

    this->pd = pd;

    //FAZER: verificar null pointer

    for (int i=0; i<pinosEntrada; i++)
    {
        this->addInputPin(tiposPinosEntrada[i]);
    }

    for (int i=0; i<pinosSaida; i++)
    {
        this->addOutputPin(tiposPinosSaida[i]);
    }

    if (DEBUG_MODE)
        cout << "\nVimusMachinePdObject constructed.";
}

/**
 * VimusMachinePdObject destructor.
 */
VimusMachinePdObject::~VimusMachinePdObject()
{
}

/**
 * Atualiza VimusMachinePdObject.
 */
void VimusMachinePdObject::update()
{
}

/**
 * Do some action before and/or after connect a pin to
 * another objects pin.
 */
bool VimusMachinePdObject::connectOutput (int outPin, VimusMachineObject * dstObj, int inPin)
{
    return dstObj->connectInput(this, outPin, inPin);
}

/**
 * Do some action before and/or after be connected by another
 * objects pin.
 */
bool VimusMachinePdObject::connectInput (VimusMachineObject * srcObj, int outPin, int inPin)
{
    cout << "\nEntrou em VimusMachinePdObject::connectInput";
    bool ret = false;
    if (srcObj->outputPins[outPin]->connect(this->inputPins[inPin]))
    {
        cout << "\nAntes de chamar pd->conectaPinos()";
        //FAZER: verificar se o Pd Realmente conectou, se não tem
        //que desfazer a conexão!!!
        this->pd->conectaPinos(srcObj->indexOnParent,
                               srcObj->outputPins[outPin]->indexOnParent,
                               this->indexOnParent,
                               this->inputPins[inPin]->indexOnParent
                              );

        ret = true;
    }
    return ret;
}

/**
 * Do some action before and/or after disconnect an output pin from
 * another objects pin.
 */
void VimusMachinePdObject::disconnectOutput (int outPin, VimusMachineObject * dstObj, int inPin)
{
    dstObj->disconnectInput(this, outPin, inPin);
}

/**
 * Do some action before and/or after disconnect an input pin from
 * another objects pin.
 */
void VimusMachinePdObject::disconnectInput (VimusMachineObject * srcObj, int outPin, int inPin)
{
    srcObj->outputPins[outPin]->disconnect(this->inputPins[inPin]);
}

/**
 * Adiciona pino de entrada. Faz overload da função de VimusMachine pra poder
 * adicionar um pino que tenha acesso a máquina do Pd.
 */
void VimusMachinePdObject :: addInputPin(int type)
{
    this->numInputs++;
    if (this->numInputs > 0)
    {
        if (type == VimusMachinePin::TYPE_VIDEO)
        {
            inputPins[this->numInputs-1] = new VimusMachinePinVideo (
                true,
                this->numInputs-1);
        }
        else if (type == VimusMachinePin::TYPE_CONTROL)
        {
            inputPins[this->numInputs-1] = new VimusMachinePinControl (
                true,
                this->numInputs-1);
        }
        else if (type == VimusMachinePin::TYPE_AUDIO)
        {
            inputPins[this->numInputs-1] = new VimusMachinePinAudio (
                true,
                this->numInputs-1,
                this->pd);
        }
        //FAZER: erro caso o tipo o pino seja inválido
    }
}

/**
 * Adiciona pino de saida. Faz overload da função de VimusMachine pra poder
 * adicionar um pino que tenha acesso a máquina do Pd.
 */
void VimusMachinePdObject :: addOutputPin(int type)
{
    this->numOutputs++;
    if (this->numOutputs > 0)
    {
        if (type == VimusMachinePin::TYPE_VIDEO)
        {
            outputPins[this->numOutputs-1] = new VimusMachinePinVideo (
                false,
                this->numOutputs-1);
        }
        else if (type == VimusMachinePin::TYPE_CONTROL)
        {
            outputPins[this->numOutputs-1] = new VimusMachinePinControl (
                false,
                this->numOutputs-1);
        }
        else if (type == VimusMachinePin::TYPE_AUDIO)
        {
            outputPins[this->numOutputs-1] = new VimusMachinePinAudio (
                false,
                this->numOutputs-1,
                this->pd);
        }
        //FAZER: erro caso o tipo o pino seja inválido
    }
}


