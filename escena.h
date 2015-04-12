/* *************************************************************************
 *   Tetrabrick v1.0                                                       *
 *   Copyright (C) 2007 by Manuel Schnidrig                                *
 *   el.manu@gmail.com                                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef ESCENA_H
#define ESCENA_H

class Escena
{
	public:
		Escena(class Nucleo *nucleo);
		virtual ~Escena();
		virtual void start(void) = 0; // Bucle principal
		virtual void stop (void) = 0; // Para la escena
		virtual void reset(void) = 0; // Resetea la escena

    protected:
        virtual void print (void) = 0; // Imprime la escena en la Display Surface
        virtual void events(void) = 0; // Maneja los eventos

		class Nucleo *nucleo;
		int i_stop; // 1 la escena esta parada, 0 lo contrario.
};

#endif
