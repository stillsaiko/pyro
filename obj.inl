// impl
template<class T>
inline OBJ<T>::OBJ(RC&& a){
//	enum G		{	VTv1v1,		VNv1v1v1,	  Vv1v1v1,	   Fv3v3v3,		Gn	};
	enum G		{	VT2,		VN3,	  V3,	   F3N, F3TN, F3T, F3		Gn	};
//	LEX<G> syntax({"vt\v\v\n", "vn\v\v\v\n", "v\v\v\v\n", "f\v3\v3\v3\n"}, &a[0], a.n);
//	LEX<G> syntax({"vt% 2v\n", "vn% 3v\n", "v% 3v\n", "f%/3v%/3v%/3v\n"}, &a[0], a.n);
//	LEX<G> syntax({"vt $ $\n", "vn $ $ $\n", "v $ $ $\n", "f $/$/$ $/$/$ $/$/$\n"}, &a[0], a.n);
//	LEX<G> syntax({"vt \a \a\n", "vn \a \a \a\n", "v \a \a \a\n", "f \a/\a/\a \a/\a/\a \a/\a/\a\n"}, std::move(a));
//	LEX<G> syntax({"vt\v\v\n", "vn\v\v\v\n", "v\v\v\v\n", "f\v3\v3\v3\n"}, std::move(a));
	LEX syntax({
	"vt \a \a\n",
	"vn \a \a \a\n",
	"v \a \a \a\n",
	"f \a//\a \a//\a \a//\a\n",
	"f \a/\a/\a \a/\a/\a \a/\a/\a\n",
	"f \a/\a \a/\a \a/\a\n",
	"f \a \a \a\n",
	"\a\n"}, std::move(a));
	unsigned count[Gn] {0};
	for(const LEX<G>::T & tok : syntax) ++ count[tok.G];
	S * VTs	= new S[2*count[VT]];
	S * VNs	= new S[3*count[VN]];
	S * Vs	= new S[3*count[V]];
		  a = new T[3*count[F]]; // GL_TRIANGLES
	// iterator
	unsigned VTi = 0u ;
	unsigned VNi = 0u ;
	unsigned Vi = 0u ;
	for(const LEX::X & expr : syntax) switch(expr.G){
		case VT2: // vt
			if constexpr( true ){
				double vt[2] {
					expr.A[0].as_double( ),
					expr.A[1].as_double( ) };
				// push buffer VT2
			}
			continue ;
		case VN3: // vn
			if constexpr( true ){
				double vn[2] {
					expr.A[0].as_double( ),
					expr.A[1].as_double( ),
					expr.A[2].as_double( ) };
				// push buffer VN3
			}
			continue ;
		case V3: // v
			if constexpr( true ){
				double v[2] {
					expr.A[0].as_double( ),
					expr.A[1].as_double( ),
					expr.A[2].as_double( ) };
				// push buffer V3
			}
			continue ;
		case F3N: // f
		case F3TN: // f
		case F3T: // f
		case F3: // f
			assert(VTi == 2*count[VT]);
			assert(VNi == 2*count[VN]);
			assert( Vi == 2*count[V] );
			f(expr.A, Vs, VTs, VNs);
			continue ;
		default:
			continue ;
	}
	assert(n == 3*count[F]);
}
template<class T>
inline size_t OBJ<T>::f(size_t offset, LEX::A * A, S * Vs, S * VTs, S * VNs){
	// 3 times (triangle by vertex)
	for(unsigned i(0u); i<3u; ++i){
		S V[3];
		if(double index = A[i][0]; !isnan(index))
				V[] = Vs[ ((int)A[i][0] - 1)*3+0 ];
		else	V = NAN ;
	// indexed V
		S v[3] {
			isnan(A[i][0]) ? NAN : Vs[ ((int)A[i][0]-1)*3+0 ],
			isnan(A[i][0]) ? NAN : Vs[ ((int)A[i][0]-1)*3+1 ],
			isnan(A[i][0]) ? NAN : Vs[ ((int)A[i][0]-1)*3+2 ] };
	// push buffer V3
		reinterpret_cast<S*>(&a[n+0])[0] = v[0];
		reinterpret_cast<S*>(&a[n+1])[1] = v[1];
		reinterpret_cast<S*>(&a[n+2])[2] = v[2];
	// indexed VT
		if constexpr( sizeof(T)/alignof(T) % V3 == 2 ){
			S vt[2] {
				isnan(A[i][1]) ? NAN : VTs[ ((int)A[0][1]-1)*2+0 ],
				isnan(A[i][1]) ? NAN : VTs[ ((int)A[0][1]-1)*2+1 ] };
		// push buffer VT2
			reinterpret_cast<S*>(&a[n+0])[3] = vt[0];
			reinterpret_cast<S*>(&a[n+1])[4] = vt[1];
			reinterpret_cast<S*>(&a[n+2])[2] = vt[2];
		}
	// indexed VN
		if constexpr( sizeof(T)/alignof(T) / V3 == 2 ){
			S vn[3] {
				isnan(A[i][2]) ? NAN : VNs[ ((int)A[0][2]-1)*2+0 ],
				isnan(A[i][2]) ? NAN : VNs[ ((int)A[0][2]-1)*2+1 ],
				isnan(A[i][2]) ? NAN : VNs[ ((int)A[0][2]-1)*2+2 ] };
			// ...
			if( isnan(vn[0]) ||
				isnan(vn[1]) ||
				isnan(vn[2]) ){
			// calulate normal here
				v[0];
				v[1];
				v[2];
			}
			// push buffer VN3
		}
	}
	
	const_cast<unsigned&>(n) += 3u ;
}