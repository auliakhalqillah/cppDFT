/*******************************************************************************
Name        : dft_code.cpp
Info        : Discrete Fourier Transform (DFT)
Written by  : Aulia Khalqillah,S.Si (2019)
Email       : auliakhalqillah.mail@gmail.com
Last Update : December 16, 2019
*******************************************************************************/
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <array>

using namespace std;

int main() {
  // const int N = 2000;
  double dt,t,f1,f2,pi,fstep,fmax,nfft,time;
  array<double,3000> x,xnoise,freq,specreal,specim,spectrum;
  int ii,i,j,k,n,N,NN;
  ofstream signal,spec;

  signal.open("signal.txt");
  N = x.size();
  NN = 2000;
  dt = 0.01;
  pi = 3.14;
  f1 = 20;
  f2 = 45;
  time = 0;
  i = 1;
  while (i<=NN) {
    // generate signal
    x[i] = sin(2*pi*f1*time)+sin(2*pi*f2*time);
    // Add noise
    x[i] = x[i]*rand();
    // Save the result to text file in 'signal variable'
    signal<<i<<"\t"<<time<<"\t"<<x[i]<<"\n";
    time = time + dt;
    ++i;
  }
  signal.close();

  // Check the number of sample data
  nfft = 1024;
  if (N<=nfft) {
    nfft = N;
  } else {
    nfft = nfft;
  }

  spec.open("spectrum.txt");
  // Generating the frequency series
  fstep = 1/dt;
  freq[1] = 0;
  j = 1;
  while (j<=nfft) {
    freq[j+1] = freq[j] + (fstep/nfft);
    ++j;
  }

  // calculating DFT
  n = 1;
  while (n<=nfft/2) {
    k = 1;
    specreal[n] = 0.0;
    specim[n] = 0.0;
    while (k<=nfft) {
      specreal[n] = specreal[n]+((x[k]*cos(2*pi*k*n/nfft)));
      specim[n] = specim[n]+((x[k]*sin(2*pi*k*n/nfft)));
      ++k;
    }
    // Calculating the absolute value
    spectrum[n] = (specreal[n]*specreal[n]) + (specim[n]*specim[n])*dt;
    // Save the result to text file in 'spec variable'
    spec<<n<<"\t"<<freq[n]<<"\t"<<specreal[n]<<"\t"<<specim[n]<<"\t"<<spectrum[n]<<"\n";
    ++n;
  }
  spec.close();
  return 0;
}
