#include "ptbin.h"

TLatex* drawLatex(Double_t x,Double_t y,char* text,Int_t textFont,Double_t textSize,Int_t colorIndex){
	TLatex *latex =new TLatex(x,y,text);
	latex->SetNDC();
	latex->SetTextFont(textFont);
	latex->SetTextSize(textSize);
	latex->SetTextColor(colorIndex);
	latex->Draw("same");
	return latex;
}

TH1D* histo(char *name, Double_t xlow, Double_t xup, Double_t ylow, Double_t yup, char* xTitle, char* yTitle){
	TH1D *dd = new TH1D(name,"",100,xlow,xup);
	dd->SetMinimum(ylow);
	dd->SetMaximum(yup);
	dd->GetXaxis()->SetTitle(xTitle);
	dd->GetYaxis()->SetTitle(yTitle);

	dd->GetXaxis()->SetTitleSize(0.055);
	dd->GetXaxis()->SetTitleOffset(0.9);
	dd->GetXaxis()->SetLabelSize(0.045);
	dd->GetYaxis()->SetTitleSize(0.055);
	dd->GetYaxis()->SetTitleOffset(1);
	dd->GetYaxis()->SetLabelSize(0.045);
	//dd->GetXaxis()->CenterTitle(kTRUE);
	//dd->GetYaxis()->CenterTitle(kTRUE);
	dd->GetXaxis()->SetNdivisions(512);
	return dd;
}
void drawTpceff()
{
	TLatex tx;
	tx.SetTextSize(0.05);
	tx.SetNDC();
	char listname[100];
    TFile *f = new TFile("../../DataMaker/embedding/BHT1_Jpsiee_eff_woTriggere.root");
	TH2F *RcWtpt    = (TH2F *)f->Get("hrcptWt");
	TH2F *RcMcWtpt  = (TH2F *)f->Get("hrcptmcWt");
	TH2F *McWtpt    = (TH2F *)f->Get("hmcptWt");
	TH2F *Rcpt      = (TH2F *)f->Get("hrcpt");
	TH2F *RcMcpt    = (TH2F *)f->Get("hrcptmc");
	TH2F *Mcpt      = (TH2F *)f->Get("hmcpt");

	TH2D *h01 = new TH2D("h01",";p_{T} (GeV/c);Counts",20,1.5,20,20,1e-10,100);
	TH2D *h03 = new TH2D("h03",";p_{T} (GeV/c);TPC tracking efficiceny",20,0,20,20,0,1.4);
	TCanvas *c3 = new TCanvas("c3", "c3",0,0,800,600);
	TCanvas *c = new TCanvas("c", "c",0,0,800,600);
	TPDF *mypdf = new TPDF("result/TPCtrackingeffHT1.pdf",111);
	mypdf->Off();
	for(int j=0;j<5;j++){
		char name1[100],name2[100],name3[100],name4[100],name5[100],name6[100];
		sprintf(name1,"RcWt_%d",j);
		sprintf(name2,"RcMcWt_%d",j);
		sprintf(name3,"McWt_%d",j);
		sprintf(name4,"Rc_%d",j);
		sprintf(name5,"RcMc_%d",j);
		sprintf(name6,"Mc_%d",j);

		TH1F *RcWt;
		TH1F *RcMcWt;
		TH1F *McWt;
		TH1F *Rc;
		TH1F *RcMc;
		TH1F *Mc;
		if(j<1){
			RcWt   = (TH1F *)RcWtpt->ProjectionX(name1,3,9)->Clone();
			RcMcWt = (TH1F *)RcMcWtpt->ProjectionX(name2,3,9)->Clone();
			McWt   = (TH1F *)McWtpt->ProjectionX(name3,3,9)->Clone();
			Rc     = (TH1F *)Rcpt->ProjectionX(name4,3,9)->Clone();
			RcMc   = (TH1F *)RcMcpt->ProjectionX(name5,3,9)->Clone();
			Mc     = (TH1F *)Mcpt->ProjectionX(name6,3,9)->Clone();
		}
		else if(j<3){
			RcWt = (TH1F *)RcWtpt->ProjectionX(name1,2*j+1,2*j+2)->Clone();
			RcMcWt = (TH1F *)RcMcWtpt->ProjectionX(name2,2*j+1,2*j+2)->Clone();
			McWt   = (TH1F *)McWtpt->ProjectionX(name3,2*j+1,2*j+2)->Clone();
			Rc     = (TH1F *)Rcpt->ProjectionX(name4,2*j+1,2*j+2)->Clone();
			RcMc   = (TH1F *)RcMcpt->ProjectionX(name5,2*j+1,2*j+2)->Clone();
			Mc     = (TH1F *)Mcpt->ProjectionX(name6,2*j+1,2*j+2)->Clone();
		}
		else if(j<4){
			RcWt = (TH1F *)RcWtpt->ProjectionX(name1,j+4,j+4)->Clone();
			RcMcWt = (TH1F *)RcMcWtpt->ProjectionX(name2,j+4,j+4)->Clone();
			McWt   = (TH1F *)McWtpt->ProjectionX(name3,j+4,j+4)->Clone();
			Rc     = (TH1F *)Rcpt->ProjectionX(name4,j+4,j+4)->Clone();
			RcMc   = (TH1F *)RcMcpt->ProjectionX(name5,j+4,j+4)->Clone();
			Mc     = (TH1F *)Mcpt->ProjectionX(name6,j+4,j+4)->Clone();
		}
		else{
			RcWt = (TH1F *)RcWtpt->ProjectionX(name1,2*j,2*j+1)->Clone();
			RcMcWt = (TH1F *)RcMcWtpt->ProjectionX(name2,2*j,2*j+1)->Clone();
			McWt   = (TH1F *)McWtpt->ProjectionX(name3,2*j,2*j+1)->Clone();
			Rc     = (TH1F *)Rcpt->ProjectionX(name4,2*j,2*j+1)->Clone();
			RcMc   = (TH1F *)RcMcpt->ProjectionX(name5,2*j,2*j+1)->Clone();
			Mc     = (TH1F *)Mcpt->ProjectionX(name6,2*j,2*j+1)->Clone();
		}
		
		RcWt->SetBinContent(0,0);
		RcMcWt->SetBinContent(0,0);
		McWt->SetBinContent(0,1e-5);
		for(int i=1;i<41;i++){
		if(McWt->GetBinContent(i)<=0||RcWt->GetBinContent(i)>McWt->GetBinContent(i))
		{RcWt->SetBinContent(i,1e-6);
		RcMcWt->SetBinContent(i,0);
		McWt->SetBinContent(i,1e-5);
		}
		}
		RcWt->SetBinContent(40,0);
		RcMcWt->SetBinContent(40,0);
		McWt->SetBinContent(40,1e-5);

		Rc->SetBinContent(0,0);
		RcMc->SetBinContent(0,1e-6);
		Mc->SetBinContent(0,1e-5);
		for(int i=1;i<1001;i++){
		if(Mc->GetBinContent(i)<=0||Rc->GetBinContent(i)>Mc->GetBinContent(i))
		{Rc->SetBinContent(i,1e-6);
		RcMc->SetBinContent(i,0);
		Mc->SetBinContent(i,1e-5);
		}
		}
		Rc->SetBinContent(1001,1e-6);
		RcMc->SetBinContent(1001,0);
		Mc->SetBinContent(1001,1e-5);

	    Rc->Rebin(20);
		RcMc->Rebin(20);
		Mc->Rebin(20);
		
		TGraphAsymmErrors *gr1=new TGraphAsymmErrors(RcWt,McWt,"B");
		gr1->BayesDivide(RcWt,McWt);
		TGraphAsymmErrors *gr2=new TGraphAsymmErrors(RcMcWt,McWt,"B");
		gr2->BayesDivide(RcMcWt,McWt);//wo Wt,only name
		TGraphAsymmErrors *gr3=new TGraphAsymmErrors(Rc,Mc,"B");
		gr3->BayesDivide(Rc,Mc);
		TGraphAsymmErrors *gr4=new TGraphAsymmErrors(RcMc,Mc,"B");
		gr4->BayesDivide(RcMc,Mc);
		TH1F *hTPCtrackingeff  = new TH1F("hTPCtrackingeff",";p_{T} (GeV/c);TPC tracking efficiceny",39,ptbin);
		sprintf(listname,"DataHT1/TPCtrackingeff_%d.dat",j);
		ofstream outdata(listname);
		for(int i=0; i<39; i++) {
			double x,y;
			int a=gr2->GetPoint(i,x,y);
			outdata << x        << "  " << gr2->GetErrorX(i)       << "  "
			        << y        << "  " << gr2->GetErrorY(i)       << endl;
			hTPCtrackingeff->SetBinContent(i+1,y);
			hTPCtrackingeff->SetBinError(i+1,gr2->GetErrorY(i));
		}
		gStyle->SetOptFit(0);
		gStyle->SetOptStat(0);
		gStyle->SetEndErrorSize(0.01);
		gStyle->SetPalette(1,0);
		c3->SetTickx();
		c3->SetTicky();
		c3->SetFillColor(10);
		c3->SetBorderMode(0);
		c3->SetBorderSize(2);
		c3->SetFrameFillColor(0);
		c3->SetFrameBorderMode(0);
		c3->SetLeftMargin(0.15);
		c3->SetBottomMargin(0.15);
		c3->SetTopMargin(0.06);
		c3->SetRightMargin(0.03);
		c3->SetLogy();
		c3->cd();

		float ymax = McWt->GetMaximum()*1000;
		h01 = new TH2D("h01",";p_{T} (GeV/c);Counts",20,0,20,20,1,ymax);
		h01->GetXaxis()->SetTitleOffset(0.9);
		h01->GetXaxis()->SetTitleSize(0.07);
		h01->GetYaxis()->SetTitleOffset(0.75);
		h01->GetYaxis()->SetTitleSize(0.07);
		h01->GetXaxis()->SetNoExponent(kTRUE);
		h01->Draw();
		McWt->SetLineWidth(1);
		McWt->SetLineColor(1);
		McWt->SetFillColor(kRed);
		McWt->SetFillStyle(1001);
		McWt->Draw("hfsame");
		RcMcWt->SetLineWidth(1);
		RcMcWt->SetLineColor(1);
		RcMcWt->SetFillColor(kBlue);
		RcMcWt->SetFillStyle(1001);
		RcMcWt->Draw("hfsame");
		TLegend *lg;
		lg = new TLegend(0.5,0.75,0.9,0.9);
		lg->SetFillStyle(0);
		lg->SetFillColor(10);
		lg->SetBorderSize(0);
		lg->SetTextSize(0.045);
		lg->AddEntry(McWt,"WO Track Quality Cuts ","f");//p");
		lg->AddEntry(RcMcWt,"W Track Quality Cuts","f");//p");
		lg->Draw();
		char txlb0[100];
		if(j==0) sprintf(txlb0,"0-60%%");
		if(j==1) sprintf(txlb0,"40-60%%");
		if(j==2) sprintf(txlb0,"20-40%%");
		if(j==3) sprintf(txlb0,"10-20%%");
		if(j==4) sprintf(txlb0,"0-10%%");
		tx.DrawLatex(0.38,0.85,txlb0);

		char gifname[100];
		sprintf(gifname,"./picHT1/TPCeffcount_%d.gif",j);
		mypdf->On();
		c3->cd();
		c3->Update();
		mypdf->NewPage();
		c3->cd();
		c3->Modified();
		mypdf->Off();
		c3->SaveAs(gifname);

		c->SetTickx();
		c->SetTicky();
		c->SetFillColor(10);
		c->SetBorderMode(0);
		c->SetBorderSize(2);
		c->SetFrameFillColor(0);
		c->SetFrameBorderMode(0);
		c->SetLeftMargin(0.15);
		c->SetBottomMargin(0.15);
		c->SetTopMargin(0.06);
		c->SetRightMargin(0.03);
		c->cd();
		h03 = new TH2D("h03",";p_{T} (GeV/c);TPC tracking efficiceny",20,0,20,20,0,1.0);
		h03->GetXaxis()->SetTitleOffset(0.9);
		h03->GetXaxis()->SetTitleSize(0.07);
		h03->GetYaxis()->SetTitleOffset(0.75);
		h03->GetYaxis()->SetTitleSize(0.07);
		h03->GetXaxis()->SetNoExponent(kTRUE);
		h03->Draw();

		//gr4->SetMarkerColor(6);
		/*gr4->SetMarkerStyle(8);
		gr4->SetMarkerSize(0.9);
		gr4->Draw("psame");
		gr3->SetMarkerColor(6);
		gr3->SetMarkerStyle(8);
		gr3->SetMarkerSize(0.9);
		gr3->Draw("psame");*/
		gr2->SetMarkerColor(6);//kGreen+1);
		gr2->SetMarkerStyle(8);
		gr2->SetMarkerSize(1.15);
		//gr2->SetLineColor(6);
		gr2->Draw("psame");
		hTPCtrackingeff->SetMarkerColor(6);//kGreen+1);
		hTPCtrackingeff->SetMarkerStyle(8);
		hTPCtrackingeff->SetMarkerSize(1.15);
		//hTPCtrackingeff->SetLineColor(6);
		hTPCtrackingeff->Draw("psame");
		/*gr1->SetMarkerColor(kRed);
		gr1->SetMarkerStyle(8);
		gr1->SetMarkerSize(0.9);
	    gr1->Draw("psame");
		lg = new TLegend(0.5,0.7,0.9,0.9);
		lg->SetFillStyle(0);
		lg->SetFillColor(10);
		lg->SetBorderSize(0);
		lg->SetTextSize(0.045);
		lg->AddEntry(gr4,"Mc/Mc","p");//p");
		lg->AddEntry(gr3,"Rc/Mc","p");//p");
		lg->AddEntry(gr2,"McWt/McWt","p");//p");
		lg->AddEntry(gr1,"RcWt/McWt","p");//p");
		lg->Draw();*/
		if(j==0) sprintf(txlb0,"0-60%%");
		if(j==1) sprintf(txlb0,"40-60%%");
		if(j==2) sprintf(txlb0,"20-40%%");
		if(j==3) sprintf(txlb0,"10-20%%");
		if(j==4) sprintf(txlb0,"0-10%%");
		tx.DrawLatex(0.43,0.86,txlb0);

		sprintf(gifname,"./picHT1/TPCtrackingeff_%d.gif",j);
		if(j<4){
			mypdf->On();
			c->Update();
			mypdf->NewPage();
			c->Modified();
			mypdf->Off();
			c->SaveAs(gifname);
		}
		else{
			mypdf->On();
			mypdf->Off();
			c->SaveAs(gifname);
		}
		gr2->SetName("TPCtrackingeff");
		char rootfilename[100];
		sprintf(rootfilename,"effroot/TPCtrackingeffHT1_%d.root",j);
		TFile* file = new TFile(rootfilename,"RECREATE");
		file->cd();
		gr2->Write();
		hTPCtrackingeff->Write();
		file->Close();
	}
	mypdf->On();
	mypdf->Close();
}

