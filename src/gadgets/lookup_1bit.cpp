// Copyright (c) 2018 HarryR
// License: LGPL-3.0+

#include "lookup_1bit.hpp"

#include "utils.hpp"

namespace ethsnarks {
	
lookup_1bit_gadget::lookup_1bit_gadget(
	ProtoboardT &in_pb,
	const std::vector<FieldT> in_constants,
	const VariableT in_bit,
	const std::string& annotation_prefix
) :
	GadgetT(in_pb, annotation_prefix),
	c(in_constants),
	b(in_bit),
	r(make_variable(in_pb, FMT(this->annotation_prefix, ".r")))
{
	assert( in_constants.size() == 2 );
}

const VariableT& lookup_1bit_gadget::result() {
	return r;
}

void lookup_1bit_gadget::generate_r1cs_constraints() {
    this->pb.add_r1cs_constraint(
        ConstraintT(
            c[0] + b*c[1] - (b*c[0]), 1, r),
            FMT(this->annotation_prefix, ".result"));
}

void lookup_1bit_gadget::generate_r1cs_witness () {
    auto i = this->pb.val(b).as_ulong();
    this->pb.val(r) = c[i];
}

// namespace ethsnarks
}
