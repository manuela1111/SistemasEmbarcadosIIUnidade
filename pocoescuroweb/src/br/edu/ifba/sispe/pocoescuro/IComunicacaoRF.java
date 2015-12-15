package br.edu.ifba.sispe.pocoescuro;

import com.sun.jna.Library;

public interface IComunicacaoRF extends Library {
	
	public int iniciar(String porta);

	public int ler();

	public int getInt();

	public int getVelocidade();
	
	public int getAltitude();

	public int getMovimento();

	public int finalizar();
}
