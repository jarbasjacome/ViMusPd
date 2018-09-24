/**
 * Copyright 2007-2017 Jarbas Jácome
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

#ifndef _PD_MAQUINA_H_
#define _PD_MAQUINA_H_

#include "Configuration.h"

#include <string>
#include <sstream>
#include <iostream>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>


/**
 * PdMaquina faz a comunicação do ViMus com o Pure Data.
 *
 * Esta classe foi desenvolvida com o inestimável apoio de
 * Miller Puckette que gentilmente me recebeu para pesquisar
 * como voluntário durante um mês no centro de música da UCSD.
 *
 * @author Jarbas Jácome
 */
class PdMaquina
{
public:

    //AFAZER:   Pensar modeladem dessa parte de visualização do áudio (buffers,
    //          comunicação vimus<->pd, etc)
    /**
     *
     */
    std::array<char, 4096> ondaSonoraDesenho;


    /**
     * Largura e altura da janela do Patch no Pure Data.
     * AFAZER: mudar para arquivo de configuração.
     */
    int PD_PATCH_LARGURA = 640;
    int PD_PATCH_ALTURA = 480;

    /**
     * Guarda a quantidade de objetos criados no patch.
     */
    int contaObjetos = 0;

    /**
     * PdMaquina construtor padrão.
     */
    PdMaquina();

    /**
     * PdMaquina destrutor padrão.
     */
    ~PdMaquina();

    /**
     * Inicia PdMaquina.
     */
    void inicia();

    /**
     * Pára PdMaquina.
     */
    void para();

    /**
     * Atualiza o estado dos objetos do ViMus que representam os objetos do Pd.
     */
    void atualiza();

    /**
     * Cria um novo objeto no Pd.
     */
    void criarObjeto(const std::string& nome, int posX, int posY);

    /**
     * Reposiciona objeto no Pd.
     */
    void reposicionaObjeto(int indice, float posX, float posY);

    /**
     * Remove um objeto do Pd.
     */
    void removeObjeto(int indice);

    /**
     * Conecta pinos de dois objetos.
     */
    bool conectaPinos(int objOrigem, int pinoSaida, int objDestino, int pinoEntrada);

    /**
     * Desconecta pinos de dois objetos.
     */
    void desconectaPinos(int objOrigem, int pinoSaida, int objDestino, int pinoEntrada);


private:

    void enviaComando (std::string msg);
    void recebeOndaSonora ();

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket_;

};

#endif //_PD_MAQUINA_H_
