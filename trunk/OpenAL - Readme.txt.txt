1) D�compressez l'archive OpenAL-1.1.rar � la racine du d�pot, si vous utilisez Mingw ou Visual Studio. Sinon, allez vous cherchez une bonne corde de chanvre bien solide et un tabouret instable.
2) Installez OpenAl en copiant les includes et les libs dans les bons dossiers de votre compilateur (pensez � faire la distinction 32/64bits)
3) Dans le SDK t�l�charg� depuis le site, dans le redist se trouve un installeur, qui sert "� faire fonctionner OpenAL sur d'autres ordinateurs". En pratique, il se contente d'extraire plusieurs DLL de mani�re tr�s crade directement dans System32. Aussi, ne le lancez pas, j'ai plac� une version compress�e de ces DLLs dans une archive du d�pot.
4) D�compressez l'archive ALUT � la base du d�pot
5) Installez ALUT - la DLL est d�j� dans l'archive avec celles d'OpenAL
6) Priez un bon coup, et essayez de compiller...


Je dois avouer que j'en ai chier des briques pour pouvoir enfin compiler. Le SVN d'OpenAL est mort, ils demandent d'utiliser cmake pour compiler les sources mais ce dernier d�clare rapidement forfait, et seules les binaires pour Visual Studio sont fournis pour Windows.
Au final, j'ai utilis� l'outil reimp (que je ne connaissais pas jusque l�) de la Mingw Tool Suite, qui sert � transformer les biblioth�ques binaires format MS au format GCC. Peu bavard mais tr�s pratique, je sens que ce petit logiciel va �tre encore tr�s utile dans le futur...