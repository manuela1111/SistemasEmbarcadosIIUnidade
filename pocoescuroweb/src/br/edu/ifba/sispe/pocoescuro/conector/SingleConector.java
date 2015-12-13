package br.edu.ifba.sispe.pocoescuro.conector;

import java.util.concurrent.Semaphore;

import br.edu.ifba.sispe.pocoescuro.IComunicacaoRF;
import br.edu.ifba.sispe.pocoescuro.Informacao;

public class SingleConector {

	private static IComunicacaoRF comRF = null;
	private static final String PORTA = "COM6";
	private static Informacao info;
	
	private static Semaphore semaforo;
	
	// vamos chamar a f�brica e ela precisa da localiza��o da biblioteca
	public static void iniciarComunicacaoRF(String libPath){
		info = new Informacao();
					comRF = FabricaConectores.getConector(libPath);
			//System.out.println("Porta: " + PORTA);
		if(comRF.iniciar(PORTA)==0){
			System.out.println("Acesso a sensores iniciado com sucesso.");
			dispensarPrimeirasLeituras();
			semaforo = new Semaphore(1,true);
		}else{
			System.out.println("N�o foi poss�vel iniciar acesso a sensores.");
		}
		}
	 public static void dispensarPrimeirasLeituras(){
		 for (int i =0; i<10; i++){
			 comRF.ler();
			 System.out.println("Dispensando leitura: "+
			 comRF.getBatimentos() + "/ " + comRF.getTemperatura() + "/ " + comRF.getMovimento());
			 
			 try {
				 //50 pq o arduino est� com sleep de 50
				Thread.sleep(50);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		 }
	 }
		
		public static int ler(){
			try {
				semaforo.acquire();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			int resultado =comRF.ler();
			if(resultado == 0){
				info.setTemperatura(comRF.getTemperatura());
				info.setBatimentos(comRF.getBatimentos());
				info.setMovimentos(comRF.getMovimento());
			}
			semaforo.release();
			return resultado;
		}
		
		public static Informacao getInformacao(){
			//Cria o sem�foro e seta todas as informa��es
			Informacao info = new Informacao();
			try {
				semaforo.acquire();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			info.setBatimentos(info.getBatimentos());
			info.setTemperatura(info.getTemperatura());
			info.setMovimentos(info.getMovimentos());
			semaforo.release();
			
			return info;
		}
		
		public static void finalizar(){
			comRF.finalizar();
		}
	
}
