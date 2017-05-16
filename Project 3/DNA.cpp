// File: DNA.cpp
// Name: Alex Leger
// Date: 3/30/2017
// Section: 05
// Email: cleger1@umbc.edu
// Desc: DNA source file

#include "DNA.h"

using namespace std;

// Note to self: Iteration through single linked lists is relatively simple, just easy to forget:
// Create an iterator (current/iterator) and get the starter (m_head) to start it
// And then iterate with a while loop with condition (current != null)
// This will end after the tail, provided the tail is properly initalized to null.
// If not, well, segfault!

// DNA constructor
DNA::DNA() {
    m_head = NULL;
    m_tail = NULL;
    m_size = 0;
}

// DNA destructor
DNA::~DNA() {
    if (m_head == NULL) return;

    Clear();

    m_head = NULL;
    m_tail = NULL;
}

// Insert a nucleotide at the end of a DNA strand
void DNA::InsertEnd(char payload) {
    // Dynamically created Nucleotide
    // Has to be deleted!
    Nucleotide *newNuc = new Nucleotide;
    newNuc->m_payload = payload;
    newNuc->m_next = NULL;

    if (m_head == NULL) {
        m_head = newNuc;
        m_tail = newNuc;
    } else {
        m_tail->m_next = newNuc;
        m_tail = newNuc;
    }
   
    m_size++;
}

// Displays DNA strand (and/or base pairs)
void DNA::Display(int numStrand) {
    switch (numStrand) {
        case 1: {
            cout << "Displaying nucleotides" << endl;
            // Just the nucleotide
            Nucleotide *current = m_head;
            int number = 0;
            while (current != NULL) {
                cout << current->m_payload << endl;
                current = current->m_next;
                number++;
            }
            cout << number << " base nucleotides listed." << endl;
            break;
        }
        case 2: {
            cout << "Displaying nucleotides and their pairs" << endl;
            // And their base pairs here
            Nucleotide *current = m_head;
            int number = 0;
            while (current != NULL) {
                cout << current->m_payload;
                if (current->m_payload == 'G') {cout << "-C" << endl;}
                if (current->m_payload == 'C') {cout << "-G" << endl;}
                if (current->m_payload == 'A') {cout << "-T" << endl;}
                if (current->m_payload == 'T') {cout << "-A" << endl;}
                current = current->m_next;
                number++;
            }            
            cout << number << " base pairs listed." << endl;
            break;
        }
        default: {
            // Error happened.
            return;
        }
    }
}

// Search the linked list for trinucleotide codons using its name and codon definition
void DNA::NumAmino(string name, string trinucleotide) {
    int numOfAcids = 0;

    // List of Nucleotides
    string LON = "";

    int iterator = 0;
    Nucleotide *current = m_head;
    while (current != NULL) {
        LON += current->m_payload;
        if (iterator % 3 == 2) {

            // Debug
            // cout << LON << "|" << trinucleotide << endl;

            if (LON == trinucleotide) {
                numOfAcids++;
            }

            LON = "";
        }
        iterator++;
        current = current->m_next;
    }
    cout << name << ": " << numOfAcids << endl;
}

// Sequence the DNA linked list
void DNA::Sequence() {
    // This is tricky
    // We want to c1reate the sequenced list and immediately delete it when we're done with it
    // No reason to keep it since it's a local function variable

    // Must be deleted!
    // Defining the array to be the total number of acids divided by three
    // This gives exactly one more space *just* incase somewhere ends up having non-triplet nucleotides
    string *listOfAcids = new string[m_size / 3];

    // First part is the iteration and creation of the nucleotide list
    int currVal = 0;
    int numTriNuc = 0;
    Nucleotide *current = m_head;
    
    // Must be deleted!
    // Now we create a new input char list
    // Iteration through the list to make sure everything works
    // We're gonna add the nucleotides to input and form the trinucleotide then translate it
    // Then send it to the list of acids.
    string s = "";
    while (current != NULL) {
        currVal++;

        s += current->m_payload;
        // Debug
        // cout << "current: " << current->m_payload << endl;

        current = current->m_next;
        if (currVal % 3 == 0) {
            // Formed a trinucleotide
            // Send it to be translated and add to array
            listOfAcids[numTriNuc] = Translate(s);
            // Reset string
            s = "";
            // Add another number to the number of trinucleotides.
            numTriNuc++;
        }
    }

    // Iterate through all the trinucleotides
    // And print them out.
    cout << "List of Amino Acids: " << endl;
    for (int i = 0; i < numTriNuc; i++) {
        cout << listOfAcids[i] << endl;
    }

    // And we're done.
    // Delete everything.
    delete[] listOfAcids;
}

// Translate the DNA
string DNA::Translate(const string trinucleotide){
  if((trinucleotide=="ATT")||(trinucleotide=="ATC")||(trinucleotide=="ATA"))
    return ("Isoleucine");
  else if((trinucleotide=="CTT")||(trinucleotide=="CTC")||(trinucleotide=="CTA")||
      (trinucleotide=="CTG")|| (trinucleotide=="TTA")||(trinucleotide=="TTG"))
    return ("Leucine");
  else if((trinucleotide=="GTT")||(trinucleotide=="GTC")||
      (trinucleotide=="GTA")||(trinucleotide=="GTG"))
    return ("Valine");
  else if((trinucleotide=="TTT")||(trinucleotide=="TTC"))
    return ("Phenylalanine");
  else if((trinucleotide=="ATG"))
    return ("Methionine");
  else if((trinucleotide=="TGT")||(trinucleotide=="TGC"))
    return ("Cysteine");
  else if((trinucleotide=="GCT")||(trinucleotide=="GCC")||
      (trinucleotide=="GCA")||(trinucleotide=="GCG"))
    return ("Alanine");
  else if((trinucleotide=="GGT")||(trinucleotide=="GGC")||
      (trinucleotide=="GGA")||(trinucleotide=="GGG"))
    return ("Glycine");
  else if((trinucleotide=="CCT")||(trinucleotide=="CCC")||
      (trinucleotide=="CCA")||(trinucleotide=="CCG"))
    return ("Proline");
  else if((trinucleotide=="ACT")||(trinucleotide=="ACC")||
      (trinucleotide=="ACA")||(trinucleotide=="ACG"))
    return ("Threonine");
  else if((trinucleotide=="TCT")||(trinucleotide=="TCC")||
      (trinucleotide=="TCA")||(trinucleotide=="TCG")||
      (trinucleotide=="AGT")||(trinucleotide=="AGC"))
    return ("Serine");
  else if((trinucleotide=="TAT")||(trinucleotide=="TAC"))
    return ("Tyrosine");
  else if((trinucleotide=="TGG"))
    return ("Tryptophan");
  else if((trinucleotide=="CAA")||(trinucleotide=="CAG"))
    return ("Glutamine");
  else if((trinucleotide=="AAT")||(trinucleotide=="AAC"))
    return ("Asparagine");
  else if((trinucleotide=="CAT")||(trinucleotide=="CAC"))
    return ("Histidine");
  else if((trinucleotide=="GAA")||(trinucleotide=="GAG"))
    return ("Glutamic acid");
  else if((trinucleotide=="GAT")||(trinucleotide=="GAC"))
    return ("Aspartic acid");
  else if((trinucleotide=="AAA")||(trinucleotide=="AAG"))
    return ("Lysine");
  else if((trinucleotide=="CGT")||(trinucleotide=="CGC")||(trinucleotide=="CGA")||
      (trinucleotide=="CGG")||(trinucleotide=="AGA")||(trinucleotide=="AGG"))
    return ("Arginine");
  else if((trinucleotide=="TAA")||(trinucleotide=="TAG")||(trinucleotide=="TGA"))
    return ("Stop");
  else
    cout << "returning unknown" << endl;
  return ("Unknown");
}

// Checks if the linked list is empty
bool DNA::IsEmpty() {
    if (m_head == NULL or m_size == 0) return true;

    return false;
}

// Sets m_size to the size of the current linked list
void DNA::SizeOf() {
    int size = 0;
    Nucleotide *current = m_head;
    while (current != NULL) {
        size++;
        current = current->m_next;
    }
    m_size = size;
}

// Clear the linked list
void DNA::Clear() {
    Nucleotide *current = m_head;
    Nucleotide *next;

    while (current != NULL) { // While the current iterator isn't null
        next = current->m_next;
        delete current;
        current = next;
    }
}