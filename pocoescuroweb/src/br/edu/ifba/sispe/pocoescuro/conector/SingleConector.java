package br.edu.ifba.sispe.pocoescuro.conector;

import java.util.concurrent.Semaphore;

import com.sun.jna.Platform;

import br.edu.ifba.sispe.pocoescuro.IComunicacaoRF;
import br.edu.ifba.sispe.pocoescuro.Informacao;

public class SingleConector {

	private static IComunicacaoRF comRF = null;
	private static String PORTA = "";
	private static Informacao info;
	
	private static Semaphore semaforo;
	
	// vamos chamar a fabrica e ela precisa da localizacao da biblioteca
	public static void iniciarComunicacaoRF(String libPath){
		
		if (Platform.isWindows()){
			PORTA = "COM6";
		}else if (Platform.isLinux()){
			PORTA = "/dev/ttyACM0";
		}
		
		info = new Informacao();
					comRF = FabricaConectores.getConector(libPath);
			//System.out.println("Porta: " + PORTA);
		if(comRF.iniciar(PORTA)==0){
			System.out.println("Acesso a sensores iniciado com sucesso.");
			dispensarPrimeirasLeituras();
			semaforo = new Semaphore(1,true);
		}else{
			System.out.println("Nao foi possivel iniciar acesso a sensores.");
		}
		}
	 public static void dispensarPrimeirasLeituras(){
		 for (int i =0; i<10; i++){
			 comRF.ler();
			 System.out.println("Dispensando leitura: "+
			 comRF.getBatimentos() + "/ " + comRF.getTemperatura() + "/ " + comRF.getMovimento());
			 
			 try {
				 //50 pq o arduino esta com sleep de 50
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
			//Cria o semaforo e seta todas as informacoes
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
