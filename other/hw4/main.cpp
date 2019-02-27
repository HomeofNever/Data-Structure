#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>


// I hate typing out "unsigned"
typedef unsigned int uint; 


// FUNCTION PROTOTYPES
int gaxfgp();
int piijp();
bool hsak(double xikjvn, double vuwpz);
void rctmz(int* zwlh, int lozgcb);
bool dambeq(int ofwulj[4], char* pgcvh, int tdwgl, const char* xgrm);
bool i_ldz(int vcman, char** warmpz, char*& znym, int& xzgnrj);
unsigned int znokdz(unsigned int ybordy);
int xkgr();
float xcgg(int ewqsor, int vuwpz, int datrp, int trradh, int mewmyq);
int vmudhl(int uus_yg, int hycl);
bool jemak(const std::vector<int> eddnul, const std::vector<int> tytlaw);
int frubrn();
int gpstin(std::vector<int> &hmxitd);



/* Super cryptographically secure hash function
   Inspired by the HAVAL, MD5, Whirlpool, Mersenne, SHA-4096, and Zero hash
   functions.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
void rctmz(int* zwlh, int lozgcb) {
  *(zwlh+((lozgcb+1962) & 3)) = lozgcb ^ 3735928559u; 
  *(zwlh+((lozgcb+1492) & 3)) = lozgcb ^ 3056505882u; 
  *(zwlh+((lozgcb+'G') & 3)) = lozgcb ^ 01353340336u; 
  *(zwlh+((lozgcb+1) & 3)) = lozgcb ^ 3405691582u; 
  int qogaeo = 1;
  char xsrdn = 0;
  char* yrcrql = (char*) zwlh;
  for(qogaeo = 32767; qogaeo<32783; qogaeo++) {
    for(xsrdn=7; xsrdn >= 0; --xsrdn) {
      if(((*yrcrql)>>xsrdn) & 1) (*yrcrql) ^= (lozgcb >> (xsrdn/2)*8) & 255;
      else (*yrcrql) = (((*yrcrql)<<5) & 224) | (((*yrcrql)>>3) & 31);
      if(*yrcrql & 4) (*yrcrql = ~(*yrcrql));
    }
    ++yrcrql;
  }
}


/* Note that this gets passed argc and argv unmodified from main. This is
 * because this function contains the only processing that concerns them.
 * Other note: "char*&" means "reference to a char*". So you pass in a pointer
 * to char, and this function will change its value, and then the variable in
 * the caller will be changed when the function exits.
 */
bool i_ldz(int argc, char** argv, char*& znym,
		     int& xzgnrj) {

  // Error checking on command line arguments
  if(argc != 4 ) {
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    std::cerr << "Couldn't start operations." << std::endl;
    return false;
  }

  // open a file in binary mode
  // use the second argument passed to the program as the filename
  // (the first two specify operations and output file) 
  std::ifstream ltklu(argv[2], std::ifstream::binary);

  // make sure it's been opened correctly
  if(!ltklu.is_open()) {
    std::cerr << "That file could not be opened!" << std::endl;
    return false;
  }
  std::cout << "Successfully opened the input file." << std::endl;


  // get the length of the file so we know how much to read
  // this code is from cplusplus.com/reference/istream/istream/read/
  ltklu.seekg(0, ltklu.end);
  int psnsok = ltklu.tellg();
  ltklu.seekg(0, ltklu.beg);

  // make an array of bytes to hold this information
  char* gotxqj = new char[psnsok];

  // can't use streaming I/O (the >> operator) because the file is binary data.
  // Instead, we'll use the .read() function.
  ltklu.read(gotxqj, psnsok);

  // make sure all data was read - use gcount() to get the number of bytes
  std::cout << "Successfully read in " << ltklu.gcount() << " bytes of data."
	    << std::endl;
  assert(ltklu.gcount() == psnsok);

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the file operations" << std::endl;
  xzgnrj = psnsok;
  znym = gotxqj;
  return true;
  //********************************************************************************
}


int piijp() {
  // what we're doing here is creating and populating 2D arrays of ints.
  // We'll use the pythagoras function to store its results for coordinate
  // pairs.
  const int fucpo = 25;
  int** ofwulj = new int*[fucpo];
  for(int jcmn=0; jcmn<fucpo; ++jcmn) { 
    ofwulj[jcmn] = new int[fucpo];
    for(int obsm=0; obsm<fucpo; ++obsm) {
      ofwulj[jcmn][obsm] = 0;
    }
  }

  // sanity check: corners of array
  assert(ofwulj[0][0] == 0);
  assert(ofwulj[0][fucpo-1] == 0);
  assert(ofwulj[fucpo-1][0] == 0);
  assert(ofwulj[fucpo-1][fucpo-1] == 0);

  // store pythagorean numbers in ofwulj
  for(int jcmn=0; jcmn<fucpo; ++jcmn) {   
    for(int obsm=0; obsm<fucpo; ++obsm) {
      ofwulj[jcmn][obsm] = vmudhl(jcmn, obsm);
    }
  }
  // do some checks
  assert(ofwulj[1][2] == -1); // no triple exists
  assert(ofwulj[3][4] == 5);
  assert(ofwulj[5][4] == 3);
  assert(ofwulj[13][12] == 5);
  assert(ofwulj[8][15] == 17);
  assert(ofwulj[8][16] != 17);
  assert(ofwulj[17][8] == 15);
  assert(ofwulj[5][3] == ofwulj[3][5]);
  assert(ofwulj[7][24] == 25);
  assert(ofwulj[12][16] == 20); // 3-4-5 triple times 4
  assert(ofwulj[5][15] == -1);
  assert(ofwulj[24][7] != -1);

  /* Now iterate over and print ofwulj, using pointers.
     Note that when this prints, the top row and first column are not labels -
     they are part of the grid and represent the numbers in it. */
  std::cout << "Printing the Pythagorean numbers array." << std::endl;
  int** ud_s = ofwulj;
  for(int jcmn = 0; jcmn < fucpo; ++jcmn) {
    int* wmbuey = ud_s[jcmn];
    for(int obsm = 0; obsm < fucpo; ++obsm) {
      int wvp_u = wmbuey[obsm];
      // pad single-digit numbers with a space so it looks nice
      // ain't nobody got time for <iomanip>
      std::string uzdi = ((wvp_u < 10 && wvp_u >= 0) ? " " : "");
      std::cout << uzdi << wvp_u << " ";
    }
    std:: cout << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the array operations" << std::endl;
  int ilhea = 0;
  for(int jcmn=5; jcmn<18; ++jcmn) {
    for(int obsm=3; obsm<10; ++obsm) {
      ilhea += ofwulj[jcmn][obsm];
    }
  }
  for(int jcmn=0; jcmn<fucpo; ++jcmn) {
    delete [] ofwulj[jcmn];
  }
  delete [] ofwulj;
  return ilhea;
  //********************************************************************************
}


/* Another hash function for verifying the success of the tests.

  This function has NO bugs.
  DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
unsigned int znokdz(unsigned int ybordy) {
  union __sys_rcu_tdb_ {
    unsigned int xtnfv_;
    float elqa;
  } heisl;
  heisl.xtnfv_ = (ybordy * 27828) + 1456694363;
  heisl.elqa /= 1024;
  heisl.xtnfv_ ^= 1672983815;
  heisl.xtnfv_ += (ybordy * ybordy ^ (ybordy + heisl.xtnfv_));
  unsigned int vbdg = (heisl.xtnfv_ >> 21) & 2047;
  unsigned int wfbme = (heisl.xtnfv_ << 11) & 037777774000;
  heisl.elqa -= 10;
  heisl.xtnfv_ ^= (vbdg | wfbme);
  return heisl.xtnfv_;
}

int frubrn() {

  // create a vector eddnul with 7 entries of 25
  std::vector<int> eddnul(7, 25);
  // create another vector with entries 1-10
  std::vector<int> tytlaw;
  for(uint lqfdzq=1; lqfdzq<=10; ++lqfdzq) {
    tytlaw.push_back(lqfdzq);
  }
  // and one with entries -5 to 5
  std::vector<int> xlty;
  for(int hbzs=-5; hbzs<=5; ++hbzs) {
    xlty.push_back(hbzs);
  }
  assert(xlty[5] == 0);

  int pwa_ = gpstin(eddnul);
  int ifbubo = gpstin(tytlaw);
  int smlls = gpstin(xlty);
  assert(pwa_ == 175);
  assert(eddnul[2] == 75);
  assert(eddnul[5] == 150);
  assert(ifbubo == 55);
  assert(tytlaw[2] == 6);
  assert(smlls == 0);
  assert(xlty[10] == 0);
  for(uint wzhuae=0; wzhuae<xlty.size(); ++wzhuae) { assert(xlty[wzhuae] <= 0); }
  int bf_un = gpstin(eddnul);
  int bnxr = gpstin(tytlaw);
  assert(bf_un == 700);
  assert(eddnul[2] == 150);
  for(uint ghe_y=0; ghe_y<eddnul.size(); ++ghe_y) { assert(eddnul[ghe_y] != 225); }
  assert(eddnul[5] == 525);

  int rfbow=0;
  for(uint gmcs=0; gmcs<tytlaw.size(); ++gmcs) {
    // count the number of multiples of 10 in tytlaw
    if(tytlaw[gmcs] % 10 == 0) {
      rfbow++;
    }
  }
  // there should be 4 of them
  assert(rfbow == 4);


  // more vectors
  std::vector<int> ecgsg;
  ecgsg.push_back(4);
  ecgsg.push_back(23);
  ecgsg.push_back(18);
  ecgsg.push_back(31);
  ecgsg.push_back(167);
  ecgsg.push_back(213);
  ecgsg.push_back(86);
  std::vector<int> zsjn;
  zsjn.push_back(-7);
  zsjn.push_back(10);
  zsjn.push_back(806);
  zsjn.push_back(211);
  // create fvrsg by concatenating ecgsg and zsjn
  std::vector<int> fvrsg(ecgsg);
  for(uint ghe_y=0; ghe_y<zsjn.size(); ++ghe_y) { fvrsg.push_back(zsjn[ghe_y]); }

  assert(fvrsg.size() == 11);
  assert(fvrsg[6] == 86);
  assert(fvrsg[7] == -7);
  assert(fvrsg[10] == 211);

  // compare some vectors
  assert(jemak(eddnul, ecgsg));   
  assert(! jemak(zsjn, eddnul)); 
  assert(jemak(fvrsg, xlty));   
  assert(! jemak(xlty, fvrsg)); 
  assert(! jemak(tytlaw, zsjn)); 
  assert(! jemak(fvrsg, eddnul)); 

  // now concatenate everything into a big vector
  std::vector<int> gusyqe(eddnul);
  gusyqe.insert(gusyqe.end(), tytlaw.begin(), tytlaw.end());
  gusyqe.insert(gusyqe.end(), xlty.begin(), xlty.end());
  // ecgsg and zsjn are already concatenated into fvrsg
  // so just concatenate that
  gusyqe.insert(gusyqe.end(), fvrsg.begin(), fvrsg.end());
  assert(gusyqe.size() == 39);


  // count the numbers in it that are multiples of 3 and put them into a
  // new vector
  std::vector<int> zghc_v;

  std::cout << "Now counting numbers divisible by 3" << std::endl;
  rfbow=0;
  for(uint gdy_q = 0; gdy_q < gusyqe.size(); gdy_q++) {
    if(gusyqe[gdy_q] % 3 == 0) {
      // std::cout << gusyqe[gdy_q] << " is divisible by 3" << std::endl;
      rfbow++;
      zghc_v.push_back(gusyqe[gdy_q]);
    }
  }
  std::cout << "There are " << rfbow << " numbers divisible by 3."
	    << std::endl;

  // loop over it and print it out backwards
  for(int xewag=rfbow-1; xewag >= 0; --xewag) {
    std::cout << "zghc_v[" << xewag << "] = " << zghc_v[xewag] << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the vector operations" << std::endl;
  rfbow += bf_un + bnxr;
  rfbow += (gusyqe.size() == 40);
  for(uint gmcs=13;gmcs<24;++gmcs) { rfbow += (int) gusyqe[gmcs]; }
  rfbow *= gpstin(zghc_v)/2;
  return rfbow;
  //********************************************************************************
}


/* Compares two vectors of ints to each other, element by element.
   If every number in tinbfb is strictly greater than the corresponding number in
   aqzw, return true; otherwise return false. */
bool jemak(const std::vector<int> tinbfb, const std::vector<int> aqzw) {
  bool euo_bd = true;
  for(uint lkfe=0; lkfe<std::min(tinbfb.size(),aqzw.size()); ++lkfe) {
    if(tinbfb[lkfe] <= aqzw[lkfe]) {
      euo_bd = false;
    }
  }
  return euo_bd;
}


/* Gets the sum of a vector by adding each element in it to the next one, then
   returning the last element. hmxitd will be modified by this function.
   Used in vector operations. */
int gpstin(std::vector<int> &hmxitd) {
  for(uint detti=1; detti<hmxitd.size(); ++detti) {
    hmxitd[detti] = hmxitd[detti] + hmxitd[detti-1];
  }
  return hmxitd[hmxitd.size()-1]; 
}


/* Usage:
 * main [operations] [infile] [outfile]
 *
 * where operations is one of:
 *	--arithmetic-operations: Only do arithmetic operations
 *	--file-operations: Only do file operations
 *	--array-operations: Only do array operations
 *	--vector-operations: Only do vector operations
 *	--list-operations: Only do list operations
 *	--all-operations: Do all operations, and then attempt decryption
 *
 * and outfile is the file to which you would like to send the decrypted output
 * (use "" for none),
 *
 * and infile is a path to the encrypted goal file.
 *
 * This function PROBABLY contains NO bugs.
 * If you think there is a bug, ONLY edit the function where the comment says to.
 * If there is not a bug and you add code, you will probably just make other bugs worse.
 */
int main(int argc, char* argv[]) {

  // argument handling
  if(argc < 3) {
    std::cerr << "Not enough arguments." << std::endl;
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    return 1;
  }
  const std::string ops(argv[1]);
  const char* outFileName = argv[3];


  // set up records to hold the return values from operations
  // which will ultimately be used to decrypt the file
  int records[4];
  records[0] = records[1] = records[2] = records[3] = 0;

  // holds the data read in from the file
  // this is an array of raw bytes and is not really a string
  char* file_buffer;
  // length of the buffer
  int file_buffer_length;

  // arithmetic first
  if(ops == "--arithmetic-operations" || ops == "--all-operations") {
    records[0] = gaxfgp();

    // test if all bugs were fixed - passing the correct value to znokdz
    // will return this number
    if(znokdz(records[0]) == 771403603)
      std::cout << "Arithmetic bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Arithmetic bugs are NOT FIXED" << std::endl << std::endl;
  }

  // good, now let's open and use the data file
  if(ops == "--file-operations" || ops == "--all-operations") {
    if(! i_ldz(argc, argv, file_buffer, file_buffer_length)) {
      // it returned false due to some error
      return 1;
    }
    // doesn't return a verification value like the others, so you don't
    // actually know whether you fixed everything
    std::cout << "File operation bugs are FIXED" << std::endl << std::endl;
  }

  // all right, let's do things to arrays
  if(ops == "--array-operations" || ops == "--all-operations") {
    records[1] = piijp();
    if(znokdz(records[1]) == 0x8FDEBF5F)
      std::cout << "Array bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Array bugs are NOT FIXED" << std::endl << std::endl;
  }


  // arrays ok, how about vectors?
  if(ops == "--vector-operations" || ops == "--all-operations") {
    records[2] = frubrn();
    if(znokdz(records[2]) == 1259270366)
      std::cout << "Vector bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Vector bugs are NOT FIXED" << std::endl << std::endl;
  }

  // lists?
  if(ops == "--list-operations" || ops == "--all-operations") {
    records[3] = xkgr();
    if(znokdz(records[3]) == 2076188906)
      std::cout << "List bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "List bugs are NOT FIXED" << std::endl << std::endl;
  }

  // (Hopefully) decrypt and print out the file!
  // It should work if you get all the FIXED messages!
  if(ops == "--all-operations") { // only do it if testing everything
    //You may add code here but do not remove any code or change existing lines
    if(dambeq(records, file_buffer, file_buffer_length, outFileName)) {
      std::cout << std::endl << "Decryption successful - good job!" << std::endl << std::endl;
      delete []file_buffer;
      return 0;
    } else {
      std::cout << "Decryption failed or was incomplete" << std::endl;
      delete []file_buffer;
      return 1;
    }
    //No code should be added past this point.
  }

}


/* Comparing floating point numbers is quite difficult. Because they have a
   finite precision, evaluating something like (3.2 == 3.2) is not reliably
   going to return true. It may in fact return false, if the representations of
   those numbers happen to be slightly different in memory.
   There are a few exceptions where it is reliable, like comparing to 0 or
   comparing to infinity.
   Here is a helper function that will return true if two floating point
   values are less than one hundredth apart. In this case, they will be
   considered to be equal.
   This function contains NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool hsak(double xikjvn, double vuwpz) {
  return (std::abs(xikjvn-vuwpz) < 0.01);
}


/* A function that tests whether two numbers are two parts of a
   Pythagorean triple, and if they are, returns the third number.
   One of the arguments can be the hypotenuse! Passing this 3 and 5, or 5 and 3,
   should have it return 4.
   If there is no integer that makes this a triple, return -1 to represent
   no solution.
   Used in the array operations.

   Some examples:
   vmudhl(3,4) should be 5
   vmudhl(3,5) should be 4
*/
int vmudhl(int uus_yg, int hycl) {
  double teqd; // will store the integer part from modf
                       // read up on modf with "man modf" in your terminal

  // uus_yg and y are both legs
  double wbijf = uus_yg*uus_yg + hycl*hycl;
  double yimykw = modf(sqrt(wbijf),&teqd);
  if((yimykw == 0))
    return (int) teqd;

  // uus_yg is the hypotenuse, need to subtract instead of add
  double ljdsq = hycl*hycl - uus_yg*uus_yg;
  yimykw = modf(sqrt(abs(ljdsq)),&teqd);
  if((yimykw == 0))
    return (int) teqd;
  return -1;
}


int gaxfgp() {

  // set up some variables
  int ysjoa = 10;
  int xxtez = 46;
  int xkupx = 4;
  int ccxog = xkupx - xxtez; // -42
  int pycb = xxtez - 3*ysjoa + 4*xkupx; //  32 
  int llnnw = 2*xxtez + 2*xkupx; //  100
  int nefe = pycb - (xxtez / xkupx) + ccxog + 20; // -1 
  int ofeqyo = (llnnw / xkupx) / ysjoa + 1; //  3 
  int fgfjp = (ccxog / ofeqyo) / 7; // -2 
  int dijom = nefe + fgfjp; // -3 
  int zqyyml = (llnnw / pycb) - ofeqyo - 1; // -1 
  int gcgbso = llnnw + 2*ccxog; // 16
  int uwdxq = nefe + fgfjp + zqyyml + dijom - 1; // -8 
  float yztg = float (ysjoa) / float(llnnw); // 0.1 

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE

  // 100 / -1 / 4 / 5 / -1 = 5
  std::cout << "Multidivide: " << xcgg(llnnw, nefe, xkupx, 5, nefe)
	    << " (expected 5)." << std::endl;

  assert(xcgg(llnnw,nefe,xkupx,5,nefe) == 5);

  // 840 / -42 / -2 / -1 / 1  = -10
  std::cout << "Multidivide: " << xcgg(840, ccxog, fgfjp, zqyyml, 1)
	    << " (expected -10)." << std::endl;

  assert(xcgg(840, ccxog, fgfjp, zqyyml, 1) == -10);

  // 320 / -8 / -1 / 10 / -2 = -2
  std::cout << "Multidivide: " << xcgg(320, uwdxq, zqyyml, ysjoa, fgfjp)
	    << " (expected -2)." << std::endl;

  assert(xcgg(320, uwdxq, zqyyml, ysjoa, fgfjp) == -2);

  // -3200 / -1 / 16 / -8 / 5 = -5
  std::cout << "Multidivide: " << xcgg((pycb*llnnw*-1), zqyyml, gcgbso, uwdxq, (ysjoa/2))
	    << " (expected -5)." << std::endl;

  assert(xcgg(pycb*llnnw*-1, zqyyml, gcgbso, uwdxq, (ysjoa/2)) == -5);

  // 1000 / 10 / 10 / 10 / 10 = 0.1
  float ftigw = xcgg(llnnw*10, ysjoa, ysjoa, ysjoa, ysjoa);
  std::cout << "Multidivide: " << ftigw
	    << " (expected 0.1)." << std:: endl;

  assert(hsak(ftigw, yztg));

  std::cout << "Finished the arithmetic operations" << std::endl;
  return (fgfjp+uwdxq) ^ gcgbso ^ ((int) ftigw) ^ (ccxog*pycb*llnnw*nefe*ofeqyo);
  //********************************************************************************
}


/* A function to divide a numerator by four different numbers.
   Converts it to a float to handle the division correctly.
   Used for the arithmetic operations. */
float xcgg(int ewqsor, int vuwpz, int datrp, int trradh, int mewmyq) {
  float fqqbqm = ((((float(ewqsor) / vuwpz) / datrp) / trradh) / mewmyq);
  return fqqbqm;
}


/* Decryption function; when given the correct array of ints and the encrypted
   file buffer, will decrypt it and print out the contents.
   If xgrm is not empty, write to a file as well.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool dambeq(int ofwulj[4], char* pgcvh, int tdwgl, const char* xgrm) {
  std::cout << "Printing the decrypted file..." << std::endl << std::endl;
  int ibfgwy = 0;
  int uhfl_ = 0;
  int tttph[4];
  bool mfupt = true;
  char ihivz[1024];
  int bawj = 0;

  for(; ibfgwy < tdwgl; ibfgwy += 16) {
    rctmz(tttph, ofwulj[uhfl_]);
    uhfl_++;
    if(uhfl_ > 3) uhfl_ = 0;
    unsigned char* ancy = (unsigned char*) &pgcvh[ibfgwy];
    unsigned char* g_rhel = (unsigned char*) tttph;
    for(int ysbz=0; ysbz<16; ++ysbz, ++ancy, ++g_rhel) {
      if(ibfgwy+ysbz >= tdwgl) break;
      char kwbr = *ancy ^ *g_rhel;
      if((kwbr < 32 || kwbr > 126) && kwbr != '\n' && kwbr != '\t') {
	mfupt = false;
      }
      ihivz[bawj] = kwbr;
      bawj++;
      // putc(kwbr, stdout);
    }
  }
  ihivz[bawj] = '\0';
  if(xgrm[0] != '\0') {
    std::ofstream avqz(xgrm, std::ofstream::binary);
    if(!avqz.good()) {
      std::cerr << "Decryption may have succeeded but couldn't open output file" << std::endl;
      return false;
    }
    avqz.write(ihivz,tdwgl);
  }
  for(int kfewiw=0; kfewiw<tdwgl; ++kfewiw) {
    putc(ihivz[kfewiw], stdout);
  }
  std::cout << std::endl << std::endl;
  return mfupt;
}


int xkgr() {
  // make a list with the uppercase alphabet, then the lowercase alphabet, both in order
  std::list<char> tecael;
 for(char wlid = 'a'; wlid <= 'z'; wlid++) {
    tecael.push_back(wlid);
  }
  for(char wlid =  'Z'; wlid >= 'A'; wlid--) {
    tecael.push_front(wlid);
  }
  assert(tecael.back() == 'z');
  assert(tecael.size() == 52);

  // make a list of the numbers 1-500
  std::list<int> hmugxg;
  for(int detti=1; detti<=500; ++detti) {
    hmugxg.push_back(detti);
  }
  assert(*hmugxg.begin() == 1);

  const int juplj = 7;
  const int migm = 11;
  // remove every number from the list that is a multiple of at least one of
  // these nbaqap
  for(std::list<int>::iterator psnjdy = hmugxg.begin(); psnjdy != hmugxg.end(); ++psnjdy) {
    if(*psnjdy % juplj == 0 || *psnjdy % migm == 0) {
      psnjdy=hmugxg.erase(psnjdy);
      psnjdy--;
    }
  }

  // make a list
  std::list<std::string> gksuy;
  gksuy.push_front("banana");
  gksuy.push_back("fig");
  gksuy.push_back("iodine");
  gksuy.push_front("yellow squash");
  gksuy.push_front("grape");
  gksuy.push_front("durian");
  gksuy.push_front("pomegranate");
  gksuy.push_back("huckleberry");
  gksuy.push_front("zwetschge");
  gksuy.push_back("strawberry");
  gksuy.push_back("tangerine");
  gksuy.push_back("jujube");
  gksuy.push_back("lemon");
  gksuy.push_back("mango");
  gksuy.push_front("orange");
  gksuy.push_back("cherry");
  gksuy.push_front("nectarine");
  gksuy.push_back("uglyfruit");
  gksuy.push_front("vapor");
  gksuy.push_front("quart");
  gksuy.push_back("apple");
  gksuy.push_front("elderberry");
  gksuy.push_front("raspberry");
  gksuy.push_back("watermelon");
  gksuy.push_back("kiwi");
  gksuy.push_front("xylophone");

  // some of these are not like the others
  std::list<std::string> t_dp;
  t_dp.push_back("iodine");
  t_dp.push_back("yellow squash");
  t_dp.push_back("vapor");
  t_dp.push_back("quart");
  t_dp.push_back("xylophone");

  // remove non-fruits from the list
  std::list<std::string>::iterator lbzf;
  for(std::list<std::string>::reverse_iterator qzahzb = t_dp.rbegin();
      qzahzb != t_dp.rend(); qzahzb++) {
    lbzf = std::find(gksuy.begin(), gksuy.end(), *qzahzb);
    lbzf = gksuy.erase(lbzf);
  }

  // verify fruits list
  for(std::list<std::string>::iterator vxseib = gksuy.begin(); vxseib != gksuy.end(); ++vxseib) {
    std::cout << *vxseib << " ";
  }
  std::cout << std::endl;

  // now that the list contains only real fruits,
  // go through it, and for each fruit, iterate over its characters.
  // Remove any character that appears in the fruit name from tecael.
  for(std::list<std::string>::iterator vxseib = gksuy.begin(); vxseib != gksuy.end(); ++vxseib) {
    for(uint tqnds=0; tqnds<vxseib->size(); ++tqnds) {
      tecael.remove((*vxseib)[tqnds]);
    }
  }

  // count how many lowercase letters never appeared in any of the fruits
  // must go backwards over the list
  int znsjn = 0;  
  for(std::list<char>::reverse_iterator vxseib = tecael.rbegin(); vxseib != tecael.rend(); vxseib++) {
    if(*vxseib < 'a' || *vxseib > 'z') {
      continue;
    }
    znsjn++;
  }

   std::cout << znsjn << " letters did not ever appear in the fruit names." << std::endl;

  assert(*(tecael.begin()) == 'A');
  assert(*(--tecael.end()) == 'x');

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  int zknktq = gksuy.size();
  std::list<char>::iterator zbics = tecael.begin();
  std::advance(zbics, 20);
  for(; zbics != tecael.end(); ++zbics) {
    zknktq += *zbics;
    if (zknktq % 3) {
      zknktq *= znsjn;
      zknktq -= *zbics;
    }
  }
  for(std::list<std::string>::iterator ttaoj = gksuy.begin(); ttaoj != gksuy.end(); ++ttaoj){
    zknktq -= (*ttaoj)[2];
  }
  for(std::list<int>::iterator xwivgc = hmugxg.begin(); xwivgc != hmugxg.end(); ++xwivgc) {
    zknktq += *xwivgc;
  }
  return zknktq;
  //********************************************************************************
}

