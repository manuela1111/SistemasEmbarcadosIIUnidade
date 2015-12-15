package br.edu.ifba.sispe.pocoescuro;

import java.util.ArrayList;
import java.util.List;

import javax.annotation.PostConstruct;
import javax.faces.bean.ManagedBean;

import org.primefaces.model.chart.MeterGaugeChartModel;

import br.edu.ifba.sispe.pocoescuro.conector.SingleConector;

@ManagedBean(name = "monitor")
public class monitor {

	// vamos configurar o medidor para identificar o valor final, inicial,
	// temperatura do componente da interface
	private MeterGaugeChartModel modeloMedidorTemperatura;
	public MeterGaugeChartModel getModeloMedidorTemperatura() {
		return modeloMedidorTemperatura;
	}

	public MeterGaugeChartModel getModeloMedidorBatimentos() {
		return modeloMedidorBatimentos;
	}

	private MeterGaugeChartModel modeloMedidorBatimentos;
	
	//Sempre q ele criar uma instancia do monitor para usar na tela ele vai passar obrigatoriamente por esse m�todo
	@PostConstruct
	public void iniciar(){
		configurarMedidores();
		
	}
	
	private void configurarMedidores(){
		modeloMedidorTemperatura = criarModeloTemperatura();
		modeloMedidorTemperatura.setTitle("Temperatura");
		modeloMedidorTemperatura.setGaugeLabel("Graus Celsius");
		modeloMedidorBatimentos = criarModeloBatimentos();
		modeloMedidorBatimentos.setTitle("Batimentos");
		modeloMedidorBatimentos.setGaugeLabel("BPM");
	}
	
	private MeterGaugeChartModel
	criarModeloTemperatura(){
		List<Number> marcadores = new ArrayList<Number>();
		marcadores.add(0);
		marcadores.add(10);
		marcadores.add(20);
		marcadores.add(30);
		marcadores.add(40);
		marcadores.add(50);
		
		return new MeterGaugeChartModel(0,marcadores);
	}
	
	private MeterGaugeChartModel
	criarModeloBatimentos(){
		List<Number> marcadores = new ArrayList<Number>();
		marcadores.add(0);
		marcadores.add(50);
		marcadores.add(75);
		marcadores.add(100);
		marcadores.add(125);
		marcadores.add(150);
		marcadores.add(175);
		marcadores.add(200);
		
		return new MeterGaugeChartModel(0,marcadores);
	}

	public boolean getMovimentoDetectado(){
		return (SingleConector.getInformacao().getMovimento()==1);
	}
	public void lerSensores() {
		// acionar a temperatura do arduino
		//SingleConector.getConector().ler();
		Informacao info = SingleConector.getInformacao();

		int altitude = info.getAltitude();
		int velocidade = info.getVelocidade();
		
		System.out.println("Altitude " + info.getAltitude());
		System.out.println("Velocidade " + info.getVelocidade());
		System.out.println("movimento " + info.getMovimento());
		
		//envia para o monitor .xhtml 
		modeloMedidorTemperatura.setValue(altitude);
		modeloMedidorBatimentos.setValue(velocidade);

		// atualizar os valores nos medidores

	}
}
