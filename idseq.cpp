#include "idseq.h"
#include "HTable.h"

IdSeq::IdSeq(const HTable &htab, const char *str)
    : ListSeq(htab.Find(str))
{

}
