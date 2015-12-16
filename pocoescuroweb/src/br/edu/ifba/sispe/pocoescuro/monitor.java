package br.edu.ifba.sispe.pocoescuro;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import javax.annotation.PostConstruct;
import javax.faces.bean.ManagedBean;

import org.primefaces.model.chart.Axis;
import org.primefaces.model.chart.AxisType;
import org.primefaces.model.chart.CartesianChartModel;
import org.primefaces.model.chart.LineChartModel;
import org.primefaces.model.chart.LineChartSeries;
import org.primefaces.model.chart.MeterGaugeChartModel;

import br.edu.ifba.sispe.pocoescuro.conector.SingleConector;

@ManagedBean(name = "monitor")
public class monitor implements Serializable {

	private LineChartModel graficoAnimal;

	private static ArrayList<Informacao> historico = new ArrayList<Informacao>();

	public LineChartModel getGraficoAnimal() {
		return graficoAnimal;
	}

	@PostConstruct
	public void iniciar() {
		configurarMedidores();
	}

	private void configurarMedidores() {
		graficoAnimal = initGraficoAnimal();
		graficoAnimal.setTitle("Animais");
		graficoAnimal.setLegendPosition("e");
		Axis yAxis = graficoAnimal.getAxis(AxisType.Y);
		yAxis.setMin(0);
		yAxis.setMax(1000);
	}

	private LineChartModel initGraficoAnimal() {
		LineChartModel model = new LineChartModel();

		LineChartSeries series1 = new LineChartSeries();
		series1.setLabel("Animal 1");

		if (!historico.isEmpty()) {
			for (Informacao informacao : historico) {
				series1.set(informacao.getVelocidade(),
						informacao.getAltitude());
			}
		}else{
			series1.set(0, 0);
		}

		LineChartSeries series2 = new LineChartSeries();
		series2.setLabel("Animal 2");
		series2.set(20,900);
		series2.set(30, 800);
		series2.set(10, 850);
		series2.set(35, 910);
		series2.set(40, 950);
		
		model.addSeries(series1);
		model.addSeries(series2);
		return model;
	}

	public boolean getMovimentoDetectado() {
		return (SingleConector.getInformacao().getMovimento() == 1);
	}

	public void lerSensores() {
		// acionar a temperatura do arduino
		// SingleConector.getConector().ler();
		Informacao info = SingleConector.getInformacao();

		int altitude = info.getAltitude();
		int velocidade = info.getVelocidade();

		System.out.println("Altitude " + info.getAltitude());
		System.out.println("Velocidade " + info.getVelocidade());
		System.out.println("movimento " + info.getMovimento());

		if (info.getMovimento() == 1) {
			historico.add(info);
			System.out.println("vel:" + info.getVelocidade());
			System.out.println("Alt:" + info.getAltitude());
		}

	}
}
