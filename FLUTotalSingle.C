#include <vector>
#include <string>
#include <TCanvas.h>
#include <TPad.h>
#include <TH1F.h>
#include <TF1.h>
#include <fstream>
#include <iostream>


void FLUTotalSingle()
{
double x, y, erry, x1, y1, erry1, x2, y2, erry2;
double ratio = x1/y1;
FILE * fp1 = fopen("DepolTotalXF.txt", "r");

FILE *fp2 = fopen("ALUTotalXF.txt", "r");

//FILE *fp4 = fopen("FLU_PT_CFR_Tab.txt", "w"); don't need for single plot b/c made with FLUTotalComp.C
int n=0;

gStyle->SetPadTopMargin(0.1);
gStyle->SetPadBottomMargin(0.18);
gStyle->SetPadLeftMargin(0.18);
gStyle->SetPadRightMargin(0.05);

////////////////////////////////////////////////////////////////////////////////
TCanvas*c01 = new TCanvas("c01", "Asymmetry", 1000,700);
c01->Divide(1,1);
//c01->Print("asymmetry.png[");
TGraphErrors*h1 = new TGraphErrors();


for(int k=0; k<13; k++){ 
fscanf(fp2, "%lf %lf %lf ", &x, &y, &erry);
fscanf(fp1, "%lf %lf %lf", &y1, &erry1, &x1); //no error calculated for pT depol (rm erry1 for Q2)
//fprintf(fp4, "%.2lf %lf %lf \n", x, y/y1, erry);

n = h1->GetN();

h1->SetPoint(n, x,-y/y1);
h1->SetPointError(n ,0, erry);

}

h1->SetLineWidth(1.5);
h1->SetMarkerColor(2);
h1->SetMarkerSize(2.5);
h1->SetMarkerStyle(20);
h1->SetName("h1");

////////////////////////////////////////////////////////////////////////////////
/* FILE *fp3 = fopen("protonAsymmetryPT_CFR.txt", "r");
int o = 0;
//TH1F*h2 = new TH1F("h2","h2",20, 0, 6.4);
TGraphErrors* h2 = new TGraphErrors();

for(int k=0; k<44; k++){ 
fscanf(fp3, "%lf %lf %lf", &x2, &y2, &erry2);

o = h2->GetN();

h2->SetPoint(o, x2, -y2);
h2->SetPointError(o ,0, erry2);

}

h2->SetLineWidth(1.5);
h2->SetMarkerColor(4);
h2->SetMarkerSize(2.5);
h2->SetMarkerStyle(20);
h2->SetName("h2");
*/

fclose(fp1);
fclose(fp2);
//fclose(fp4);

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
TCanvas*c03 = new TCanvas("c03", "Asymmetry", 1000, 700);
c03->Divide(1,1);
//c03->Print("asymmetryCompare.png[");
TMultiGraph*h3 = new TMultiGraph();  //two in one!!

c03->cd(1);
h3->Add(h1);
//h3->Add(h2);

h3->GetXaxis()->SetTitle("x_{F}");
h3->GetXaxis()->SetTitleSize(0.09);
h3->GetXaxis()->SetLabelSize(0.06);
h3->GetXaxis()->SetTitleOffset(0.8);
h3->GetXaxis()->SetTitleFont(12);
h3->GetYaxis()->SetTitle("F_{LU}"); // F_{LU} = A_{LU}/epsilon factor
h3->GetYaxis()->SetTitleSize(0.09);
h3->GetYaxis()->SetLabelSize(0.06);
h3->GetYaxis()->SetTitleOffset(0.7);


gPad->Modified();
gPad->Update();
   
h3->Draw("AP");
h3->GetXaxis()->SetRangeUser(-0.8, 0.6);     //xF (-0.8, 0.6); Q2 (0.0, 6.0); pT (0.0, 1.3)
h3->GetYaxis()->SetRangeUser(-0.04, 0.04); //xF (-0.04, 0.04); Q2 (-0.05, 0.005); pT_TFR (-0.09, 0.0); pT_CFR (-0.02, 0.17)

	//TLine *line = new TLine(-0.8,0.0,0.706,0.0);
	//line->SetLineColor(1);
	//line->SetLineWidth(1);
	//line->Draw();
	
////////////////////////////////////////////////////////////////////////////////
/*
auto legend = new TLegend(0.85,0.25,0.95,0.4); 
legend->AddEntry("h1","F_{LU}","p");
legend->AddEntry("h2","A_{LU}","p");


legend->Draw(); */
c03->Update();
gPad->Modified();
gPad->Update();

//c03->Print("FLUTotalQ2Comp.pdf");
c03->Print("FLU_XF_a.png");

}


