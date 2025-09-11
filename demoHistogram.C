void demoHistogram() 
{
    TCanvas * c2 = new TCanvas("c", "c", 600, 600);
    auto demo = new TH1F("h", "h", 80, -40, 40);
    TRandom3 r;
    for (int i=0;i<15000;i++) {
        demo->Fill(r.Gaus(0,7));
    }
    demo->Draw();
    c2->Draw();
}