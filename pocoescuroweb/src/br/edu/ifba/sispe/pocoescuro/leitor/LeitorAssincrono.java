package br.edu.ifba.se.babycare.leitor;

import java.util.concurrent.Semaphore;

import br.edu.ifba.sispe.pocoescuro.conector.SingleConector;

public class LeitorAssincrono implements Runnable{
	
	private boolean continuar;

	@Override
	public void run() {
		// TODO Auto-generated method stub
		continuar = true;
		while(continuar){
		
			
			SingleConector.ler();
			try {
				Thread.sleep(50);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public void parar(){
		continuar = false;
	}

}
