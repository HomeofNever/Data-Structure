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
int uzlaki();
int xujz();
bool bdjq(double fxuus, double qykrae);
void aslg(int* einv_, int ha_ted);
bool ssrow(int xsdus[4], char* wrfren, int xqis, const char* wngmq);
bool teqd(int vsqn, char** xqdix, char*& lojt_w, int& knphh);
unsigned int upjmub(unsigned int rqbdw);
int zbna();
float qaut(int hhyo, int qykrae, int vuwpz, int rtazkk, int tval);
int ofxtfp(int tdeik, int ribzwv);
bool clnx(const std::vector<int> frubrn, const std::vector<int> jahtu);
int taysxt();
int wwqub(std::vector<int> &apsa);



/* Note that this gets passed argc and argv unmodified from main. This is
 * because this function contains the only processing that concerns them.
 * Other note: "char*&" means "reference to a char*". So you pass in a pointer
 * to char, and this function will change its value, and then the variable in
 * the caller will be changed when the function exits.
 */
bool teqd(int argc, char** argv, char*& lojt_w,
          int& knphh) {

  // Error checking on command line arguments
  if(argc != 4) {
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    std::cerr << "Couldn't start operations." << std::endl;
    return false;
  }

  // open a file in binary mode
  // use the second argument passed to the program as the filename
  // (the first two specify operations and output file)
  std::ifstream qqioi(argv[2], std::ifstream::binary);

  // make sure it's been opened correctly
  if(!qqioi.is_open()) {
    std::cerr << "That file could not be opened!" << std::endl;
    return false;
  }
  std::cout << "Successfully opened the input file." << std::endl;

  int nciy;

  // make an array of bytes to hold this information
  char * nzlrb = new char[nciy];

  // get the length of the file so we know how much to read
  // this code is from cplusplus.com/reference/istream/istream/read/
  qqioi.seekg(0, qqioi.end);
  nciy = qqioi.tellg();
  qqioi.seekg(0, qqioi.beg);

  // can't use streaming I/O (the >> operator) because the file is binary data.
  // Instead, we'll use the .read() function.
  qqioi.read(nzlrb, nciy);

  // make sure all data was read - use gcount() to get the number of bytes
  std::cout << "Successfully read in " << qqioi.gcount() << " bytes of data."
            << std::endl;
  assert(qqioi.gcount() == nciy);

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the file operations" << std::endl;
  knphh = nciy;
  lojt_w = nzlrb;
  return true;
  //********************************************************************************
}


/* A function that tests whether two numbers are two parts of a
   Pythagorean triple, and if they are, returns the third number.
   One of the arguments can be the hypotenuse! Passing this 3 and 5, or 5 and 3,
   should have it return 4.
   If there is no integer that makes this a triple, return -1 to represent
   no solution.
   Used in the array operations.

   Some examples:
   ofxtfp(3,4) should be 5
   ofxtfp(3,5) should be 4
*/
int ofxtfp(int tdeik, int ribzwv) {
  double prdp; // will store the integer part from modf
  // read up on modf with "man modf" in your terminal

  // tdeik and y are both legs
  float yfxeo = tdeik*tdeik + ribzwv*ribzwv;
  float mont = modf(sqrt(yfxeo), &prdp);
  if(mont == 0)
    return (int) prdp;

  // tdeik is the hypotenuse, need to subtract instead of add
  float lfxayq;
  if (tdeik > ribzwv)
  {
    lfxayq = tdeik*tdeik - ribzwv*ribzwv;
  } else {
    lfxayq = ribzwv*ribzwv - tdeik*tdeik;
  }

  mont = modf(sqrt(lfxayq), &prdp);
  if(mont == 0)
    return (int) prdp;

  return -1;
}

int taysxt() {

  // create a vector frubrn with 7 entries of 25
  std::vector<int> frubrn(7, 25);
  // create another vector with entries 1-10
  std::vector<int> jahtu;
  for(uint idirjf=1; idirjf<=10; ++idirjf) {
    jahtu.push_back(idirjf);
  }
  // and one with entries -5 to 5
  std::vector<int> nrkhfm;
  for(int hxym=-5; hxym<=5; ++hxym) {
    nrkhfm.push_back(hxym);
  }
  assert(nrkhfm[5] == 0);

  int hycl = wwqub(frubrn);
  int hxzpt = wwqub(jahtu);
  int ebmz = wwqub(nrkhfm);
  assert(hycl == 175);
  assert(frubrn[2] == 75);
  assert(frubrn[5] == 150);
  assert(hxzpt == 55);
  assert(jahtu[2] == 6);
  assert(ebmz == 0);
  assert(nrkhfm[10] == 0);
  for(uint ufqb=0; ufqb<nrkhfm.size(); ++ufqb) { assert(nrkhfm[ufqb] <= 0); }
  int iimme = wwqub(frubrn);
  int kfewiw = wwqub(jahtu);
  assert(iimme == 700);
  assert(frubrn[2] == 150);
  for(uint lunsul=0; lunsul<frubrn.size(); ++lunsul) { assert(frubrn[lunsul] != 225); }
  assert(frubrn[5] == 525);

  int u_qg = 0;
  for(uint jywuv=0; jywuv<jahtu.size(); ++jywuv) {
    // count the number of multiples of 10 in jahtu
    if(jahtu[jywuv] % 10 == 0) {
      u_qg++;
    }
  }
  // there should be 4 of them
  assert(u_qg == 4);


  // more vectors
  std::vector<int> emtc;
  emtc.push_back(4);
  emtc.push_back(23);
  emtc.push_back(18);
  emtc.push_back(31);
  emtc.push_back(167);
  emtc.push_back(213);
  emtc.push_back(86);
  std::vector<int> fzezqd;
  fzezqd.push_back(-7);
  fzezqd.push_back(10);
  fzezqd.push_back(806);
  fzezqd.push_back(211);
  // create tvrfm by concatenating emtc and fzezqd
  std::vector<int> tvrfm(emtc);
  for(uint lunsul=0; lunsul<fzezqd.size(); ++lunsul) { tvrfm.push_back(fzezqd[lunsul]); }

  assert(tvrfm.size() == 11);
  assert(tvrfm[6] == 86);
  assert(tvrfm[7] == -7);
  assert(tvrfm[10] == 211);

  // compare some vectors
  assert(clnx(frubrn, emtc));
  assert(! clnx(fzezqd, frubrn));
  assert(clnx(tvrfm, nrkhfm));
  assert(! clnx(nrkhfm, tvrfm));
  assert(! clnx(jahtu, fzezqd));
  assert(! clnx(tvrfm, frubrn));

  // now concatenate everything into a big vector
  std::vector<int> gqszp(frubrn);
  gqszp.insert(gqszp.end(), jahtu.begin(), jahtu.end());
  gqszp.insert(gqszp.end(), nrkhfm.begin(), nrkhfm.end());
  // emtc and fzezqd are already concatenated into tvrfm
  // so just concatenate that
  gqszp.insert(gqszp.end(), tvrfm.begin(), tvrfm.end());
  assert(gqszp.size() == 39);


  // count the numbers in it that are multiples of 3 and put them into a
  // new vector
  std::vector<int> xdhiq;
  u_qg = 0;

  std::cout << "Now counting numbers divisible by 3" << std::endl;
  for(uint fqfkg = 0; fqfkg < gqszp.size(); fqfkg+=1) {
    if(gqszp[fqfkg] % 3 == 0) {
      // std::cout << gqszp[fqfkg] << " is divisible by 3" << std::endl;
      u_qg++;
      xdhiq.push_back(gqszp[fqfkg]);
    }
  }
  std::cout << "There are " << u_qg << " numbers divisible by 3."
            << std::endl;

  // loop over it and print it out backwards
  for(int migm=u_qg-1; migm >= 0; --migm) {
    std::cout << "xdhiq[" << migm << "] = " << xdhiq[migm] << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the vector operations" << std::endl;
  u_qg += iimme + kfewiw;
  u_qg += (gqszp.size() == 40);
  for(uint jywuv=13;jywuv<24;++jywuv) { u_qg += (int) gqszp[jywuv]; }
  u_qg *= wwqub(xdhiq)/2;
  return u_qg;
  //********************************************************************************
}

/* A function to divide a numerator by four different numbers.
   Converts it to a float to handle the division correctly.
   Used for the arithmetic operations. */
float qaut(int hhyo, int qykrae, int vuwpz, int rtazkk, int tval) {
  float wlid = (((((float)hhyo / (float)qykrae) / (float)vuwpz) / (float)rtazkk) / (float)tval);
  return wlid;
}


int zbna() {
  // make a list with the uppercase alphabet, then the lowercase alphabet, both in order
  std::list<char> fkciz;
  for(char pqic = 'A'; pqic <= 'Z'; pqic++) {
    fkciz.push_back(pqic);
  }
  for(char pqic = 'a'; pqic <= 'z'; pqic++) {
    fkciz.push_back(pqic);
  }
  assert(fkciz.back() == 'z');
  assert(fkciz.size() == 52);

  // make a list of the numbers 1-500
  std::list<int> nvlahj;
  for(int nmuf=1; nmuf<=500; ++nmuf) {
    nvlahj.push_back(nmuf);
  }
  assert(*nvlahj.begin() == 1);

  const int zsclz = 7;
  const int loies = 11;
  // remove every number from the list that is a multiple of at least one of
  // these sfekx
  for(std::list<int>::iterator swem = nvlahj.begin(); swem != nvlahj.end();) {
    if(*swem % zsclz == 0 || *swem % loies == 0) {
      swem = nvlahj.erase(swem);
    } else {
      swem++;
    }
  }

  // make a list
  std::list<std::string> bijqwy;
  bijqwy.push_front("banana");
  bijqwy.push_back("fig");
  bijqwy.push_back("iodine");
  bijqwy.push_front("yellow squash");
  bijqwy.push_front("grape");
  bijqwy.push_front("durian");
  bijqwy.push_front("pomegranate");
  bijqwy.push_back("huckleberry");
  bijqwy.push_front("zwetschge");
  bijqwy.push_back("strawberry");
  bijqwy.push_back("tangerine");
  bijqwy.push_back("jujube");
  bijqwy.push_back("lemon");
  bijqwy.push_back("mango");
  bijqwy.push_front("orange");
  bijqwy.push_back("cherry");
  bijqwy.push_front("nectarine");
  bijqwy.push_back("uglyfruit");
  bijqwy.push_front("vapor");
  bijqwy.push_front("quart");
  bijqwy.push_back("apple");
  bijqwy.push_front("elderberry");
  bijqwy.push_front("raspberry");
  bijqwy.push_back("watermelon");
  bijqwy.push_back("kiwi");
  bijqwy.push_front("xylophone");

  // some of these are not like the others
  std::list<std::string> gersa;
  gersa.push_back("iodine");
  gersa.push_back("yellow squash");
  gersa.push_back("vapor");
  gersa.push_back("quart");
  gersa.push_back("xylophone");

  // remove non-fruits from the list
  std::list<std::string>::iterator bkrm;
  for(std::list<std::string>::reverse_iterator bkkep = gersa.rbegin();
      bkkep != gersa.rend(); bkkep++) {
    bkrm = std::find(bijqwy.begin(), bijqwy.end(), *bkkep);
    bijqwy.erase(bkrm);
  }

  // verify fruits list
  for(std::list<std::string>::iterator aujsga = bijqwy.begin(); aujsga != bijqwy.end(); ++aujsga) {
    std::cout << *aujsga << " ";
  }
  std::cout << std::endl;

  // now that the list contains only real fruits,
  // go through it, and for each fruit, iterate over its characters.
  // Remove any character that appears in the fruit name from fkciz.
  for(std::list<std::string>::iterator aujsga = bijqwy.begin(); aujsga != bijqwy.end(); ++aujsga) {
    for(uint xygg=0; xygg<aujsga->size(); ++xygg) {
      fkciz.remove((*aujsga)[xygg]);
    }
  }

  // count how many lowercase letters never appeared in any of the fruits
  // must go backwards over the list
  int g_wyb = 0;
  for(std::list<char>::iterator aujsga = fkciz.end(); aujsga != fkciz.begin(); aujsga--) {
    if(*aujsga < 'a' || *aujsga > 'z') {
      continue;
    }
    g_wyb++;
  }

  std::cout << g_wyb << " letters did not ever appear in the fruit names." << std::endl;

  assert(*fkciz.begin() == 'A');
  assert(*(--fkciz.end()) == 'x');

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  int hwqpp = bijqwy.size();
  std::list<char>::iterator nxhg = fkciz.begin();
  std::advance(nxhg, 20);
  for(; nxhg != fkciz.end(); ++nxhg) {
    hwqpp += *nxhg;
    if (hwqpp % 3) {
      hwqpp *= g_wyb;
      hwqpp -= *nxhg;
    }
  }
  for(std::list<std::string>::iterator tzhx = bijqwy.begin(); tzhx != bijqwy.end(); ++tzhx){
    hwqpp -= (*tzhx)[2];
  }
  for(std::list<int>::iterator pqme = nvlahj.begin(); pqme != nvlahj.end(); ++pqme) {
    hwqpp += *pqme;
  }
  return hwqpp;
  //********************************************************************************
}


/* Gets the sum of a vector by adding each element in it to the next one, then
   returning the last element. apsa will be modified by this function.
   Used in vector operations. */
int wwqub(std::vector<int> &apsa) {
  for(uint nmuf=1; nmuf<apsa.size(); ++nmuf) {
    apsa[nmuf] = apsa[nmuf] + apsa[nmuf-1];
  }
  return apsa[apsa.size() - 1];
}


/* Another hash function for verifying the success of the tests.

  This function has NO bugs.
  DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
unsigned int upjmub(unsigned int rqbdw) {
  union __sys_rcu_tdb_ {
      unsigned int dgcuai;
      float ztursm;
  } jcmn;
  jcmn.dgcuai = (rqbdw * 27828) + 1456694363;
  jcmn.ztursm /= 1024;
  jcmn.dgcuai ^= 1672983815;
  jcmn.dgcuai += (rqbdw * rqbdw ^ (rqbdw + jcmn.dgcuai));
  unsigned int twmf_i = (jcmn.dgcuai >> 21) & 2047;
  unsigned int oleglh = (jcmn.dgcuai << 11) & 037777774000;
  jcmn.ztursm -= 10;
  jcmn.dgcuai ^= (twmf_i | oleglh);
  return jcmn.dgcuai;
}

int uzlaki() {

  // set up some variables
  int xleony = 10;
  int bfnfk_ = 46;
  int ymvu = 4;
  int bmxu = ymvu - bfnfk_; // -42
  int ukts_v = bfnfk_ - 3*xleony + 4*ymvu; //  32
  int wbijf = 2*bfnfk_ + 2*ymvu; //  100
  int gqrre = ukts_v - (bfnfk_ / ymvu) + bmxu + 20; // -1
  int agaal = (wbijf / ymvu) / xleony + ((wbijf / ymvu) % xleony > 0); //  3
  int dvyftr = (bmxu / agaal) / 7; // -2
  int qangui = gqrre + dvyftr; // -3
  int ognpw = (wbijf / ukts_v) - agaal - 1; // -1
  int zghc_v = wbijf + 2*bmxu; // 16
  int qidm = gqrre + dvyftr + ognpw + qangui -1; // -8
  float mzucv = (float)xleony / wbijf; // 0.1

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE

  // 100 / -1 / 4 / 5 / -1 = 5
  std::cout << "Multidivide: " << qaut(wbijf, gqrre, ymvu, 5, gqrre)
    << " (expected 5)." << std::endl;

  assert(qaut(wbijf,gqrre,ymvu,5,gqrre) == 5);

  // 840 / -42 / -2 / -1 / 1  = -10
  std::cout << "Multidivide: " << qaut(840, bmxu, dvyftr, ognpw, 1)
    << " (expected -10)." << std::endl;

  assert(qaut(840, bmxu, dvyftr, ognpw, 1) == -10);

  // 320 / -8 / -1 / 10 / -2 = -2
  std::cout << "Multidivide: " << qaut(320, qidm, ognpw, xleony, dvyftr)
    << " (expected -2)." << std::endl;

  assert(qaut(320, qidm, ognpw, xleony, dvyftr) == -2);

  // -3200 / -1 / 16 / -8 / 5 = -5
  std::cout << "Multidivide: " << qaut((ukts_v*wbijf*-1), ognpw, zghc_v, qidm, (xleony/2))
    << " (expected -5)." << std::endl;

  assert(qaut(ukts_v*wbijf*-1, ognpw, zghc_v, qidm, (xleony/2)) == -5);

  // 1000 / 10 / 10 / 10 / 10 = 0.1
  float xtapdh = qaut(wbijf*10, xleony, xleony, xleony, xleony);
  std::cout << "Multidivide: " << xtapdh
    << " (expected 0.1)." << std:: endl;

  assert(bdjq(xtapdh, mzucv));

  std::cout << "Finished the arithmetic operations" << std::endl;
  return (dvyftr+qidm) ^ zghc_v ^ ((int) xtapdh) ^ (bmxu*ukts_v*wbijf*gqrre*agaal);
  //********************************************************************************
}


/* Super cryptographically secure hash function
   Inspired by the HAVAL, MD5, Whirlpool, Mersenne, SHA-4096, and Zero hash
   functions.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
void aslg(int* einv_, int ha_ted) {
  *(einv_+((ha_ted+1962) & 3)) = ha_ted ^ 3735928559u;
  *(einv_+((ha_ted+1492) & 3)) = ha_ted ^ 3056505882u;
  *(einv_+((ha_ted+'G') & 3)) = ha_ted ^ 01353340336u;
  *(einv_+((ha_ted+1) & 3)) = ha_ted ^ 3405691582u;
  int ewqsor = 1;
  char acgjz = 0;
  char* flbfdw = (char*) einv_;
  for(ewqsor = 32767; ewqsor<32783; ewqsor++) {
    for(acgjz=7; acgjz >= 0; --acgjz) {
      if(((*flbfdw)>>acgjz) & 1) (*flbfdw) ^= (ha_ted >> (acgjz/2)*8) & 255;
      else (*flbfdw) = (((*flbfdw)<<5) & 224) | (((*flbfdw)>>3) & 31);
      if(*flbfdw & 4) (*flbfdw = ~(*flbfdw));
    }
    ++flbfdw;
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
bool bdjq(double fxuus, double qykrae) {
  return (std::abs(fxuus-qykrae) < 0.01);
}


/* Compares two vectors of ints to each other, element by element.
   If every number in kfkzrc is strictly greater than the corresponding number in
   honiyd, return true; otherwise return false. */
bool clnx(const std::vector<int> kfkzrc, const std::vector<int> honiyd) {
  bool uuuo = true;
  for(uint usqdc=0; usqdc<kfkzrc.size(); ++usqdc) {
    if(kfkzrc[usqdc] <= honiyd[usqdc]) {
      uuuo = false;
      break;
    }
  }
  return uuuo;
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
    records[0] = uzlaki();

    // test if all bugs were fixed - passing the correct value to upjmub
    // will return this number
    if(upjmub(records[0]) == 771403603)
      std::cout << "Arithmetic bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Arithmetic bugs are NOT FIXED" << std::endl << std::endl;
  }

  // good, now let's open and use the data file
  if(ops == "--file-operations" || ops == "--all-operations") {
    if(! teqd(argc, argv, file_buffer, file_buffer_length)) {
      // it returned false due to some error
      return 1;
    }
    // doesn't return a verification value like the others, so you don't
    // actually know whether you fixed everything
    std::cout << "File operation bugs are FIXED" << std::endl << std::endl;
  }

  // all right, let's do things to arrays
  if(ops == "--array-operations" || ops == "--all-operations") {
    records[1] = xujz();
    if(upjmub(records[1]) == 0x8FDEBF5F)
      std::cout << "Array bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Array bugs are NOT FIXED" << std::endl << std::endl;
  }


  // arrays ok, how about vectors?
  if(ops == "--vector-operations" || ops == "--all-operations") {
    records[2] = taysxt();
    if(upjmub(records[2]) == 1259270366)
      std::cout << "Vector bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Vector bugs are NOT FIXED" << std::endl << std::endl;
  }

  // lists?
  if(ops == "--list-operations" || ops == "--all-operations") {
    records[3] = zbna();
    if(upjmub(records[3]) == 2076188906)
      std::cout << "List bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "List bugs are NOT FIXED" << std::endl << std::endl;
  }

  // (Hopefully) decrypt and print out the file!
  // It should work if you get all the FIXED messages!
  if(ops == "--all-operations") { // only do it if testing everything
    //You may add code here but do not remove any code or change existing lines
    if(ssrow(records, file_buffer, file_buffer_length, outFileName)) {
      std::cout << std::endl << "Decryption successful - good job!" << std::endl << std::endl;
      return 0;
    } else {
      std::cout << "Decryption failed or was incomplete" << std::endl;
      return 1;
    }
    //No code should be added past this point.
  }

}


int xujz() {
  // what we're doing here is creating and populating 2D arrays of ints.
  // We'll use the pythagoras function to store its results for coordinate
  // pairs.
  const int ohmgu = 25;
  int** xsdus = new int*[ohmgu];
  int** neug = new int*[ohmgu];
  for(int yphmro=0; yphmro<ohmgu; ++yphmro) {
    xsdus[yphmro] = new int[ohmgu];
    neug[yphmro] = new int[ohmgu];
    for(int adne=0; adne<ohmgu; ++adne) {
      xsdus[yphmro][adne] = 0;
      neug[yphmro][adne] = 0;
    }
  }

  // sanity check: corners of array
  assert(xsdus[1][1] == 0);
  assert(xsdus[1][ohmgu - 1] == 0);
  assert(xsdus[ohmgu - 1][1] == 0);
  assert(xsdus[ohmgu - 1][ohmgu - 1] == 0);

  // store pythagorean numbers in xsdus
  for(int yphmro=0; yphmro<ohmgu; ++yphmro) {
    for(int adne=0; adne<ohmgu; ++adne) {
      xsdus[yphmro][adne] = ofxtfp(yphmro, adne);
      neug[yphmro][adne] = xsdus[yphmro][adne] * ofxtfp(adne, yphmro);
    }
  }
  // do some checks
  assert(xsdus[1][2] == -1); // no triple exists
  assert(xsdus[3][4] == 5);
  assert(xsdus[5][4] == 3);
  assert(xsdus[13][12] == 5);
  assert(xsdus[8][15] == 17);
  assert(xsdus[8][16] != 17);
  assert(xsdus[17][8] == 15);
  assert(xsdus[5][3] == xsdus[3][5]);
  assert(xsdus[7][24] == 25);
  assert(xsdus[12][16] == 20); // 3-4-5 triple times 4
  assert(xsdus[5][15] == -1);
  assert(xsdus[24][7] != -1);

  /* Now iterate over and print xsdus, using pointers.
     Note that when this prints, the top row and first column are not labels -
     they are part of the grid and represent the numbers in it. */
  std::cout << "Printing the Pythagorean numbers array." << std::endl;
  int** zqyyml = xsdus;
  int** flfl = neug;

  for(int yphmro = 0; yphmro < ohmgu; ++yphmro, ++zqyyml, ++flfl) {
    int* lhzzn = *zqyyml;
    for(int adne = 0; adne < ohmgu; ++adne, ++lhzzn) {
      int gldg = *lhzzn;
      // pad single-digit numbers with a space so it looks nice
      // ain't nobody got time for <iomanip>
      std::string zwmm = ((gldg < 10 && gldg >= 0) ? " " : "");
      std::cout << zwmm << *lhzzn << " ";
    }
    std:: cout << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the array operations" << std::endl;
  int tdqci = 0;
  for(int yphmro=5; yphmro<18; ++yphmro) {
    for(int adne=3; adne<10; ++adne) {
      tdqci += xsdus[yphmro][adne];
    }
  }
  for(int yphmro=0; yphmro<ohmgu; ++yphmro) {
    delete [] xsdus[yphmro];
  }
  delete [] xsdus;
  return tdqci;
  //********************************************************************************
}


/* Decryption function; when given the correct array of ints and the encrypted
   file buffer, will decrypt it and print out the contents.
   If wngmq is not empty, write to a file as well.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool ssrow(int xsdus[4], char* wrfren, int xqis, const char* wngmq) {
  std::cout << "Printing the decrypted file..." << std::endl << std::endl;
  int jfsq = 0;
  int hmzd = 0;
  int gsdtu[4];
  bool ozns = true;
  char offgq[1024];
  int tfgnwq = 0;

  for(; jfsq < xqis; jfsq += 16) {
    aslg(gsdtu, xsdus[hmzd]);
    hmzd++;
    if(hmzd > 3) hmzd = 0;
    unsigned char* jrack = (unsigned char*) &wrfren[jfsq];
    unsigned char* izonm = (unsigned char*) gsdtu;
    for(int vvgst=0; vvgst<16; ++vvgst, ++jrack, ++izonm) {
      if(jfsq+vvgst >= xqis) break;
      char dgavfo = *jrack ^ *izonm;
      if((dgavfo < 32 || dgavfo > 126) && dgavfo != '\n' && dgavfo != '\t') {
        ozns = false;
      }
      offgq[tfgnwq] = dgavfo;
      tfgnwq++;
      // putc(dgavfo, stdout);
    }
  }
  offgq[tfgnwq] = '\0';
  if(wngmq[0] != '\0') {
    std::ofstream fcgvs_(wngmq, std::ofstream::binary);
    if(!fcgvs_.good()) {
      std::cerr << "Decryption may have succeeded but couldn't open output file" << std::endl;
      return false;
    }
    fcgvs_.write(offgq,xqis);
  }
  for(int hxbj=0; hxbj<xqis; ++hxbj) {
    putc(offgq[hxbj], stdout);
  }
  std::cout << std::endl << std::endl;
  return ozns;
}
