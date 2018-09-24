/**
 * Copyright 2007-2015 Jarbas Jácome
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

#include "PdMaquina.h"

using namespace boost::asio::ip;


/**
 * PdMaquina construtor padrão.
 */
PdMaquina :: PdMaquina () : socket_(this->io_service)
{
    if (DEBUG_MODE)
        std::cout << "\nPdMaquina construida.";

    try
    {
        tcp::resolver resolver(io_service);
        tcp::resolver::query query("localhost", "17780");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        boost::asio::connect(socket_, endpoint_iterator);
    }

    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

}

/**
* PdMaquina destrutor padrão.
*/
PdMaquina :: ~PdMaquina()
{

}

/**
 * Inicia PdMaquina.
 */
void PdMaquina :: inicia()
{

}

/**
 * Pára PdMaquina.
 */
void PdMaquina :: para()
{

}

/**
 * Atualiza o estado dos objetos do ViMus que representam os objetos do Pd.
 */
void PdMaquina :: atualiza()
{

}

/**
 * Cria um novo objeto no Pd.
 */
void PdMaquina :: criarObjeto(const std::string& nome, int posX, int posY)
{
    std::stringstream cmd;
    cmd << "obj " << posX << " " << posY << " " << nome << ";";
    enviaComando (cmd.str());
}

/**
 * Reposiciona objeto no Pd.
 */
void PdMaquina :: reposicionaObjeto(int indice, float posX, float posY)
{

}

/**
 * Remove um objeto do Pd.
 */
void PdMaquina :: removeObjeto(int indice)
{

}

/**
 * Conecta pinos de dois objetos.
 */
bool PdMaquina :: conectaPinos(int objOrigem, int pinoSaida, int objDestino, int pinoEntrada)
{
    bool ret = true;

    std::stringstream cmd;
    //FAZER: Resolver modelagem: VimusMachineEditor em que ter acesso ao indiceNoPd!!!
    //esse + 3 é uma gambiarra, são 3 objetos no ViMus.pd
    cmd << "connect " << objOrigem + 3 << " " << pinoSaida << " "
                      << objDestino + 3 << " " << pinoEntrada << ";";
    enviaComando (cmd.str());

    //FAZER: Verificar se Pd conectou realmente.

    return ret;
}

/**
 * Desconecta pinos de dois objetos.
 */
void PdMaquina :: desconectaPinos(int objOrigem, int pinoSaida, int objDestino, int pinoEntrada)
{

}

/**
 * Envia comando para o Pure Data
 */
void PdMaquina :: enviaComando (std::string msg)
{
    boost::system::error_code ignored_error;

    //FAZER: utilizar async_write com callback em vez de write()
    boost::asio::write(socket_, boost::asio::buffer(msg), ignored_error);

    //FAZER: TIRA ISSO DAQUI!!!
//    recebeOndaSonora();
//    for (int i=0; i<500; i++){
//       std::cout << ondaSonoraDesenho[i];
//    }
}

void PdMaquina ::recebeOndaSonora() {
    boost::system::error_code ignored_error;

    boost::asio::read(socket_, boost::asio::buffer(ondaSonoraDesenho), ignored_error);
}
