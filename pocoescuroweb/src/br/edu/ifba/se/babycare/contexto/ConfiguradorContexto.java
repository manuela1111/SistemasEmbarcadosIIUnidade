package br.edu.ifba.se.babycare.contexto;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;

import br.edu.ifba.se.babycare.leitor.LeitorAssincrono;
import br.edu.ifba.sispe.pocoescuro.conector.SingleConector;

import com.sun.faces.config.ConfigureListener;

public class ConfiguradorContexto extends ConfigureListener{
	private LeitorAssincrono leitor;
	private Thread tLeitor;
	
	@Override
	public void contextInitialized(ServletContextEvent sce){		
		super.contextInitialized(sce);
		//vamos verificar se vai funcionar
		System.out.println("Iniciando o tomcat...");
		ServletContext sc = sce.getServletContext();
		
		String libPath = sc.getRealPath("/WEB-INF/lib/");
		System.out.println("libPath conf contexto: "+ libPath);
		SingleConector.iniciarComunicacaoRF(libPath);
		leitor = new LeitorAssincrono();
		tLeitor = new Thread(leitor);
		tLeitor.start();
	}
	
	public void contextDestroyed(ServletContextEvent sce){
		leitor.parar();
		try {
			tLeitor.join();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("Finalizando o tomcat...");
		SingleConector.finalizar();
		super.contextDestroyed(sce);
		
	}

}
