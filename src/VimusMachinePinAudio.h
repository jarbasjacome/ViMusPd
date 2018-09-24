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

#ifndef _VIMUSMACHINEPINAUDIO_H_
#define _VIMUSMACHINEPINAUDIO_H_

#include <stdlib.h>

#include "VimusMachinePin.h"
#include "PdMaquina.h"

/**
 * VimusMachinePinAudio represents a control Pin.
 *
 * @author Jarbas Jácome
 */
class VimusMachinePinAudio : public VimusMachinePin
{
    public:

        /**
         * VimusMachinePinAudio constructor.
         */
        VimusMachinePinAudio (bool input, int index, PdMaquina* pd);

        /**
         * VimusMachinePinAudio destructor.
         */
        ~VimusMachinePinAudio();

        /**
         * Connect to an input pin.
         */
		bool connect(VimusMachinePinAudio *pin);

        /**
         * Disconnect a pin.
         */
        bool disconnect(VimusMachinePinAudio *pin);

        VimusMachinePinAudio * connections[MAX_CONNECTIONS];

    private:

        PdMaquina* pd;

};

#endif //_VIMUSMACHINEPINAUDIO_H_
