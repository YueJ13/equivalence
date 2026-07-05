# Code and Data for "Determining the Equivalence of Small Zero-One Reaction Networks"

This repository contains the code and data accompanying the preprint:

**["Determining the Equivalence of Small Zero-one Reaction Networks"](https://doi.org/10.48550/arXiv.2503.00008)**  
by Yue Jiao and Xiaoxian Tang.

---

## Overview

The implementation follows **Algorithm 1** from the paper, which determines the equivalence of zero-one reaction networks. The workflow is divided into four sequential steps, each handled by a separate script.

---

## Instructions

All files required to run the algorithm are located under the path:  
`equivalence/new/`

### Step 1–4: 
Run **`Equivalence-1.nb`** in Mathematica.  
This notebook implements Steps 1 through 4 of Algorithm 1.

### Step 5: 
First, compile and run **`generate_reff.c`** in C.  
This program compute the reduced row echelon form of the stoichiometric matrix **N**.
Then, compile and run **`Equivalent-2.c`** in C.  
This implements Step 5 of Algorithm 1.

### Step 6–7: 
Run **`Equicalent-3.nb`** in Mathematica.  
This notebook completes Steps 6 and 7 of Algorithm 1.

---


## Contact

For questions or issues, please contact the authors directly.

---
