/**
 * Copyright 2007-2011 Jarbas Jácome
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

#ifndef _VIMUSMACHINEPDOBJECT_H_
#define _VIMUSMACHINEPDOBJECT_H_

#include <stdlib.h>
#include "Configuration.h"

#include "PdMaquina.h"
#include "VimusMachineObject.h"

#include <string>

/**
 * VimusMachinePdObject é uma classe abstrata que representa
 * objetos do Pure Data.
 *
 * @author Jarbas Jácome
 */
class VimusMachinePdObject : public VimusMachineObject
{
    public:

        /**
         * VimusMachinePdObject default constructor.
         */
        VimusMachinePdObject(const std::string& nome,
                             int pinosEntrada, int tiposPinosEntrada[],
                             int pinosSaida, int tiposPinosSaida[],
                             int indice, PdMaquina* pd);

        /**
         * VimusMachinePdObject destructor.
         */
        virtual ~VimusMachinePdObject();

        /**
         * Atualiza VimusMachinePdObject.
         */
        void update();

		/**
		 * Do some action before and/or after connect an output pin to
		 * another objects input pin.
		 */
		bool connectOutput (int outPin, VimusMachineObject * dstObj, int inPin);

		/**
		 * Do some action before and/or after connect an input pin to
		 * another objects output pin.
		 */
		bool connectInput (VimusMachineObject * srcObj, int outPin, int inPin);

		/**
		 * Do some action before and/or after disconnect an output pin from
		 * another objects pin.
		 */
		void disconnectOutput (int outPin, VimusMachineObject * dstObj, int inPin);

		/**
		 * Do some action before and/or after disconnect an input pin from
		 * another objects pin.
		 */
		void disconnectInput (VimusMachineObject * srcObj, int outPin, int inPin);

		void addInputPin(int type);

		void addOutputPin(int type);

    private:

        int indiceNoPd;

        PdMaquina * pd;

};

#endif //_VIMUSMACHINEPDOBJECT_H_
