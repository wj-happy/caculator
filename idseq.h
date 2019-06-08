#ifndef IDSEQ_H
#define IDSEQ_H

#include "List.h"
class HTable;

class IdSeq : public ListSeq
{
public:
    IdSeq(HTable const & htab, char const *str );
};

#endif // IDSEQ_H
