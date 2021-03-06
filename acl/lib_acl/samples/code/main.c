#include "lib_acl.h"

static struct {
	unsigned short id;
	char *entity;
} html_charset[] = {
    {   32, "&nbsp;"    }, {  34, "&quot;"    }, {  34, "&quot;"    }, {  38, "&amp;"     },
    {   38, "&amp;"     }, {  39, "&apos;"    }, {  60, "&lt;"      }, {  60, "&lt;"      },
    {   62, "&gt;"      }, {  62, "&gt;"      }, { 160, "&nbsp;"    }, { 161, "&iexcl;"   },
    {  162, "&cent;"    }, { 163, "&pound;"   }, { 164, "&curren;"  }, { 165, "&yen;"     },
    {  166, "&brvbar;"  }, { 167, "&sect;"    }, { 168, "&uml;"     }, { 169, "&copy;"    },
    {  170, "&ordf;"    }, { 171, "&laquo;"   }, { 172, "&not;"     }, { 173, "&shy;"     },
    {  174, "&reg;"     }, { 175, "&macr;"    }, { 176, "&deg;"     }, { 177, "&plusmn;"  },
    {  178, "&sup2;"    }, { 179, "&sup3;"    }, { 180, "&acute;"   }, { 181, "&micro;"   },
    {  182, "&para;"    }, { 183, "&middot;"  }, { 184, "&cedil;"   }, { 185, "&sup1;"    },
    {  186, "&ordm;"    }, { 187, "&raquo;"   }, { 188, "&frac14;"  }, { 189, "&frac12;"  },
    {  190, "&frac34;"  }, { 191, "&iquest;"  }, { 192, "&Agrave;"  }, { 193, "&Aacute;"  },
    {  194, "&Acirc;"   }, { 195, "&Atilde;"  }, { 196, "&Auml;"    }, { 197, "&Aring;"   },
    {  198, "&AElig;"   }, { 199, "&Ccedil;"  }, { 200, "&Egrave;"  }, { 201, "&Eacute;"  },
    {  202, "&Ecirc;"   }, { 203, "&Euml;"    }, { 204, "&Igrave;"  }, { 205, "&Iacute;"  },
    {  206, "&Icirc;"   }, { 207, "&Iuml;"    }, { 208, "&ETH;"     }, { 209, "&Ntilde;"  },
    {  210, "&Ograve;"  }, { 211, "&Oacute;"  }, { 212, "&Ocirc;"   }, { 213, "&Otilde;"  },
    {  214, "&Ouml;"    }, { 215, "&times;"   }, { 216, "&Oslash;"  }, { 217, "&Ugrave;"  },
    {  218, "&Uacute;"  }, { 219, "&Ucirc;"   }, { 220, "&Uuml;"    }, { 221, "&Yacute;"  },
    {  222, "&THORN;"   }, { 223, "&szlig;"   }, { 224, "&agrave;"  }, { 225, "&aacute;"  },
    {  226, "&acirc;"   }, { 227, "&atilde;"  }, { 228, "&auml;"    }, { 229, "&aring;"   },
    {  230, "&aelig;"   }, { 231, "&ccedil;"  }, { 232, "&egrave;"  }, { 233, "&eacute;"  },
    {  234, "&ecirc;"   }, { 235, "&euml;"    }, { 236, "&igrave;"  }, { 237, "&iacute;"  },
    {  238, "&icirc;"   }, { 239, "&iuml;"    }, { 240, "&eth;"     }, { 241, "&ntilde;"  },
    {  242, "&ograve;"  }, { 243, "&oacute;"  }, { 244, "&ocirc;"   }, { 245, "&otilde;"  },
    {  246, "&ouml;"    }, { 247, "&divide;"  }, { 248, "&oslash;"  }, { 249, "&ugrave;"  },
    {  250, "&uacute;"  }, { 251, "&ucirc;"   }, { 252, "&uuml;"    }, { 253, "&yacute;"  },
    {  254, "&thorn;"   }, { 255, "&yuml;"    }, { 338, "&OElig;"   }, { 339, "&oelig;"   },
    {  352, "&Scaron;"  }, { 353, "&scaron;"  }, { 376, "&Yuml;"    }, { 402, "&fnof;"    },
    {  710, "&circ;"    }, { 732, "&tilde;"   }, { 913, "&Alpha;"   }, { 914, "&Beta;"    },
    {  915, "&Gamma;"   }, { 916, "&Delta;"   }, { 917, "&Epsilon;" }, { 918, "&Zeta;"    },
    {  919, "&Eta;"     }, { 920, "&Theta;"   }, { 921, "&Iota;"    }, { 922, "&Kappa;"   },
    {  923, "&Lambda;"  }, { 924, "&Mu;"      }, { 925, "&Nu;"      }, { 926, "&Xi;"      },
    {  927, "&Omicron;" }, { 928, "&Pi;"      }, { 929, "&Rho;"     }, { 931, "&Sigma;"   },
    {  932, "&Tau;"     }, { 933, "&Upsilon;" }, { 934, "&Phi;"     }, { 935, "&Chi;"     },
    {  936, "&Psi;"     }, { 937, "&Omega;"   }, { 945, "&alpha;"   }, { 946, "&beta;"    },
    {  947, "&gamma;"   }, { 948, "&delta;"   }, { 949, "&epsilon;" }, { 950, "&zeta;"    },
    {  951, "&eta;"     }, { 952, "&theta;"   }, { 953, "&iota;"    }, { 954, "&kappa;"   },
    {  955, "&lambda;"  }, { 956, "&mu;"      }, { 957, "&nu;"      }, { 958, "&xi;"      },
    {  959, "&omicron;" }, { 960, "&pi;"      }, { 961, "&rho;"     }, { 962, "&sigmaf;"  },
    {  963, "&sigma;"   }, { 964, "&tau;"     }, { 965, "&upsilon;" }, { 966, "&phi;"     },
    {  967, "&chi;"     }, { 968, "&psi;"     }, { 969, "&omega;"   }, { 977, "&thetasym" },
    {  978, "&upsih;"   }, { 982, "&piv;"     }, {8194, "&ensp;"    }, {8195, "&emsp;"    },
    { 8201, "&thinsp;"  }, {8204, "&zwnj;"    }, {8205, "&zwj;"     }, {8206, "&lrm;"     },
    { 8207, "&rlm;"     }, {8211, "&ndash;"   }, {8212, "&mdash;"   }, {8216, "&lsquo;"   },
    { 8217, "&rsquo;"   }, {8218, "&sbquo;"   }, {8220, "&ldquo;"   }, {8221, "&rdquo;"   },
    { 8222, "&bdquo;"   }, {8224, "&dagger;"  }, {8225, "&Dagger;"  }, {8226, "&bull;"    },
    { 8230, "&hellip;"  }, {8240, "&permil;"  }, {8242, "&prime;"   }, {8243, "&Prime;"   },
    { 8249, "&lsaquo;"  }, {8250, "&rsaquo;"  }, {8254, "&oline;"   }, {8260, "&frasl;"   },
    { 8364, "&euro;"    }, {8465, "&image;"   }, {8472, "&weierp;"  }, {8476, "&real;"    },
    { 8482, "&trade;"   }, {8501, "&alefsym;" }, {8592, "&larr;"    }, {8593, "&uarr;"    },
    { 8594, "&rarr;"    }, {8595, "&darr;"    }, {8596, "&harr;"    }, {8629, "&crarr;"   },
    { 8656, "&lArr;"    }, {8657, "&uArr;"    }, {8658, "&rArr;"    }, {8659, "&dArr;"    },
    { 8660, "&hArr;"    }, {8704, "&forall;"  }, {8706, "&part;"    }, {8707, "&exist;"   },
    { 8709, "&empty;"   }, {8711, "&nabla;"   }, {8712, "&isin;"    }, {8713, "&notin;"   },
    { 8715, "&ni;"      }, {8719, "&prod;"    }, {8721, "&sum;"     }, {8722, "&minus;"   },
    { 8727, "&lowast;"  }, {8730, "&radic;"   }, {8733, "&prop;"    }, {8734, "&infin;"   },
    { 8736, "&ang;"     }, {8743, "&and;"     }, {8744, "&or;"      }, {8745, "&cap;"     },
    { 8746, "&cup;"     }, {8747, "&int;"     }, {8756, "&there4;"  }, {8764, "&sim;"     },
    { 8773, "&cong;"    }, {8776, "&asymp;"   }, {8800, "&ne;"      }, {8801, "&equiv;"   },
    { 8804, "&le;"      }, {8805, "&ge;"      }, {8834, "&sub;"     }, {8835, "&sup;"     },
    { 8836, "&nsub;"    }, {8838, "&sube;"    }, {8839, "&supe;"    }, {8853, "&oplus;"   },
    { 8855, "&otimes;"  }, {8869, "&perp;"    }, {8901, "&sdot;"    }, {8968, "&lceil;"   },
    { 8969, "&rceil;"   }, {8970, "&lfloor;"  }, {8971, "&rfloor;"  }, {9001, "&lang;"    },
    { 9002, "&rang;"    }, {9674, "&loz;"     }, {9824, "&spades;"  }, {9827, "&clubs;"   },
    { 9829, "&hearts;"  }, {9830, "&diams;"   }
};

static void test_map2(void)
{
	unsigned int i, n;
	unsigned short k;
	unsigned char h, l;

	n = sizeof(html_charset) / sizeof(html_charset[0]);

	for (i = 0; i < n; i++) {
		k = html_charset[i].id;
		h = (unsigned char) (k >> 8);
		l = (unsigned char) (k & 0xFF) ;
		if (k > 255 && (h == 0 || l == 0))
			printf("id: %d = 0\n", html_charset[i].id);
	}
}

static void create_map2(void)
{
	unsigned int   i, j, n;

	n = sizeof(html_charset) / sizeof(html_charset[0]);

	for (i = 0; i < n; i++) {
		const char *ptr = html_charset[i].entity;
		if (ptr == NULL)
			continue;
		for (j = 0; j < i; j++) {
			if (html_charset[j].entity == NULL)
				continue;
			if (strcmp(ptr, html_charset[j].entity) == 0) {
				html_charset[j].entity = NULL;
				break;
			}
		}
	}

	printf("#ifndef	__HTML_CHARSET_INCLUDE_H__\n");
	printf("#define	__HTML_CHARSET_INCLUDE_H__\n");
	printf("\n");

	printf("static const char *html_charmap[] = {\n");
	for (i = 0; i < 65535; i++) {
		if (i > 0) {
			if (i % 8 == 0)
				printf(",\n\t");
			else
				printf(", ");
		} else
			printf("\t");
		for (j = 0; j < n; j++) {
			if (html_charset[j].entity && html_charset[j].id == i)
				break;
		}
		if (j < n)
			printf("\"%s\"", html_charset[j].entity);
		else
			printf("NULL");
	}
	printf("\n};\n");

	printf("\ntypedef struct {\n"
		"\tunsigned short  ch;\n"
		"\tconst char *txt;\n"
		"\tsize_t  len;\n"
		"} HTML_SPEC;\n"
		"\n"
		"static const HTML_SPEC html_tab[] = {\n"
	);
	for (i = 0; i < n; i++) {
		if (html_charset[i].entity == NULL)
			continue;
		printf("\t{ %u, \"%s\", sizeof(\"%s\") - 1 },\n",
			html_charset[i].id, html_charset[i].entity, html_charset[i].entity);
	}
	printf("};\n\n");
	printf("#endif\n");
}

/*----------------------------------------------------------------------------*/

typedef struct HTML_SPEC_TBL
{
	const char  ch;
	const char *txt;
} HTML_SPEC_TBL;

static const HTML_SPEC_TBL __tab[] = {
	{ '<', "&lt;" },
	{ '>', "&gt;" },
	{ '&', "&amp;" },
	{ '\'', "&apos;" },
	{ '\"', "&quot;" },
	{ 0, 0 }
};

static void create_map1(void)
{
	int   i, j;

	for (i = 0; i < 255; i++) {
		if (i > 0) {
			if (i % 8 == 0)
				printf(",\r\n");
			else
				printf(", ");
		}
		for (j = 0; __tab[j].ch; j++) {
			if (__tab[j].ch == i)
				break;
		}
		if (__tab[j].ch)
			printf("\"%s\"", __tab[j].txt);
		else
			printf("NULL");
	}
	printf("\r\n");
}

int main(void)
{
	const char *src = "%E4%B8%AD%E5%9B%BD%0A%E4%B8%AD%E5%9B%BD%0A%E4%B8%AD%E5%9B%BD";
/*
	char  buf[256], *dst;
*/
	char  *dst;

	if (0) {
		create_map1();
		return (0);
	} else if (1) {
		create_map2();
		return (0);
	} else if (2) {
		test_map2();
		return (0);
	}

	printf("src(%s)\n", src);
	dst = acl_url_decode(src, NULL);
	printf("dst(%s)\n", dst);

/*
	if (acl_utf8_to_gb2312(dst, strlen(dst), buf, sizeof(buf)) > 0)
		printf("ok, buf(%s)\n", buf);
	else
		printf("error\n");

	src = "??????";
	if (acl_utf8_to_gb2312(src, strlen(src), buf, sizeof(buf)) > 0)
		printf("ok, buf(%s)\n", buf);
	else
		printf("error\n");
*/
	return (0);
}
